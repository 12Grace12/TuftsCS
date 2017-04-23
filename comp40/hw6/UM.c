/*
 * UM.c
 * by Ben Tanen and Rebecca Larson
 *
 * The implementation for the UM ADT
 * Includes definitions of all functions used by UM_T
 * UM is a struct containing 8 registers, a program counter and
 * a sequence of memory segments (also keeps a stack of available IDs to use)
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <bitpack.h>
#include <assert.h>

#include "UM.h"
#include "UM_instructions.h"
#include "seg.h"
#include "seq.h"
#include "stack.h"

#define NUM_REG 8
#define HINT_SEQ_SIZE 1000
#define INSTRUCTION_LENGTH 4

struct UM_T {
        uint32_t registers[NUM_REG];
        uint32_t p_counter;
        Stack_T  available_IDs;
        Seq_T    segments; 
}; 

static void (*instructions[13]) (UM_T UM, int rA, int rB, int rC) = {
        conditional_move,
        segmented_load,
        segmented_store,
        addition,
        multiplication,
        division,
        bitwise_NAND,
        halt,
        map_segment,
        unmap_segment,
        output,
        input,
        load_program, 
};

/***************************/
/* static helper functions */
/***************************/

/* returns a particular segment from the sequence */
static inline Seg_T UM_get_seg(UM_T UM, unsigned segID)
{
        return Seq_get(UM->segments, segID);
}

/* returns the uint32_t value of a given input from a file */
static /* inline */ uint32_t read_instruction_line(FILE *fp)  
{
        uint32_t instruction = 0;

        /* read the correct number of characters and bitpack them */
        for (int i = INSTRUCTION_LENGTH - 1; i >= 0; i--) {
                int c = fgetc(fp);
                if (c == EOF) break;
                instruction = Bitpack_newu(instruction, 8, i * 8, c);
        }
        
        return instruction; 
}


/***********************/
/* interface functions */
/***********************/

/* initalizes a new UM */
/* hasn't yet stored program instructions -> see read_program() */
UM_T     UM_new()
{
        /* allocate necessary size and initalize values & registers */
        UM_T um = malloc(sizeof(*um));
        assert(um != NULL);
        
        um->p_counter = 0;
        um->available_IDs = Stack_new();

        for (int i = 0; i < NUM_REG; i++) {
                (um->registers)[i] = 0;
        }

        /* make initial dummy m[0] */
        um->segments = Seq_new(HINT_SEQ_SIZE);
        Seq_addhi(um->segments, Seg_new(5, 0));

        return um;
}

/* gets a word from a specified segment */
uint32_t UM_get_segment_word(UM_T UM, uint32_t segID, unsigned offset)
{
        /* make sure UM exists, the segID is within valid range, and refers */
        /* to mapped segment */
        assert(UM);
        assert((uint32_t)Seq_length(UM->segments) > segID);
        assert(Seg_is_mapped(UM_get_seg(UM, segID)));

        return Seg_get_word(UM_get_seg(UM, segID), offset);
}

/* sets a word value for a specified segment */
void     UM_set_segment_word(UM_T UM, uint32_t segID, 
                             unsigned offset, uint32_t word)
{
        /* make sure UM exists, the segID is within valid range, and refers */
        /* to mapped segment */
        assert(UM);
        assert((uint32_t)Seq_length(UM->segments) > segID);
        assert(Seg_is_mapped(UM_get_seg(UM, segID)));

        Seg_put_word(UM_get_seg(UM, segID), offset, word);
}

/* gets the length of a specified segment (by segID) */
int      UM_get_segment_length(UM_T UM, uint32_t segID)
{
        /* make sure UM exists and segID is valid */
        assert(UM);
        assert((uint32_t)Seq_length(UM->segments) > segID);

        return Seg_length(UM_get_seg(UM, segID));
}

/* maps a segment to specified size (num of words to hold) */
uint32_t UM_map_segment(UM_T UM, unsigned numWords)
{
        assert(UM);

        /* gets ID from stack, maps segment */
        if (Stack_empty(UM->available_IDs) == 0) {
                uint32_t segID = 
                              (uint32_t)(uintptr_t)Stack_pop(UM->available_IDs);
                Seg_T seg = UM_get_seg(UM, segID);
                Seg_map(seg, numWords);
                return segID;
        }

        /* need to add on new segment to sequence */
        Seg_T new_seg = Seg_new(numWords, Seq_length(UM->segments));
        Seq_addhi(UM->segments, new_seg);

        return Seg_ID(new_seg);
}

/* unmaps segment, making it unusable to UM until re-map */
void     UM_unmap_segment(UM_T UM, uint32_t segID)
{
        /* make sure UM exists and segID in valid range */
        assert(UM);
        assert((uint32_t)Seq_length(UM->segments) > segID);

        /* unmap segment */
        Seg_unmap(UM_get_seg(UM, segID));

        /* push segID back onto stack of available IDs */
        Stack_push(UM->available_IDs, (void *)(uintptr_t)segID);
}

/* gets the value of a specified register */
uint32_t UM_get_register(UM_T UM, unsigned reg)
{
        /* make sure UM exists and register number is valid */
        assert(UM);
        assert(reg < 8);

        return (UM->registers)[reg];
}

/* sets the value of a specified register */
void     UM_set_register(UM_T UM, unsigned reg, uint32_t word)
{
        /* make sure UM exists and register number is valid */
        assert(UM);
        assert(reg < 8);

        (UM->registers)[reg] = word;
}

/* reads the instructions of the given input file program */
/* stores these instructions in m[0] of the given UM */
void     UM_read_program(UM_T UM, FILE *fp)
{
        /* read in each instruction to new sequence */
        Seq_T instructions = Seq_new(5);
        while (true) {
                /* read each input line as uint32_t instuction */
                uint32_t instruction = read_instruction_line(fp);

                /* make sure we didn't hit EOF during read_instruction */
                if (feof(fp) != 0) break;

                /* add instruction onto sequence of program instructions */
                Seq_addhi(instructions, (void *)(uintptr_t)instruction);
        } 

        /* re-map segment 0 to appropriate size for instructions */
        UM_unmap_segment(UM, 0);
        UM_map_segment(UM, Seq_length(instructions));

        /* get each instruction from sequence, put in new segment 0 */
        for (int i = 0; i < Seq_length(instructions); i++) {
                uint32_t instruction = 
                                 (uint32_t)(uintptr_t)Seq_get(instructions, i);
                UM_set_segment_word(UM, 0, i, instruction);
        }

        /* free sequence of instructions */
        Seq_free(&instructions);
}

/* runs the program instructions until halt is called or a fail case is hit */
void     UM_run_program(UM_T UM)
{
        while (true) {
                /* assert program counter inside bounds of m[0] */
                assert(UM->p_counter <= 
                                       (uint32_t)Seg_length(UM_get_seg(UM, 0)));

                /* get the instruction and its opcode */
                uint32_t instruction = UM_get_segment_word(UM, 0, 
                                                           UM->p_counter);
                int op_code = Bitpack_getu(instruction, 4, 28);

                /* check for invalid opcode */
                assert(op_code >= 0 && op_code <= 13);

                /* instruction is load_value */
                if (op_code == 13) {
                        int regA  = Bitpack_getu(instruction, 3, 25);
                        int value = Bitpack_getu(instruction, 25, 0);
                        load_value(UM, regA, value);

                /* instruction is halt */
                } else if (op_code == 7) {
                        break;

                /* all other instructions */
                } else {
                        int regA = Bitpack_getu(instruction, 3, 6);
                        int regB = Bitpack_getu(instruction, 3, 3);
                        int regC = Bitpack_getu(instruction, 3, 0);

                        instructions[op_code](UM, regA, regB, regC);
                }

                /* move program counter accordingly */
                /* instruction is load_program and p_counter moves */ 
                if (op_code == 12) {
                        int regC = Bitpack_getu(instruction, 3, 0);
                        UM->p_counter = (UM->registers)[regC];
                
                /* all other instructions */
                } else (UM->p_counter)++;
        }
}

/* free associated memory for UM */
void     UM_free(UM_T *UM_p)
{
        assert(UM_p && *UM_p);
        UM_T um = *UM_p;
        
        /* free every segment inside sequence */
        for (int i = 0; i < Seq_length(um->segments); i++) {
                Seg_T seg = UM_get_seg(um, i);
                Seg_free(&seg);
        }

        /* free whole sequence and struct */
        Seq_free(&(um->segments));
        free(um);
}

