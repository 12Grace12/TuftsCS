/*
 * UM.c (optimized)
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
#include <assert.h>
#include <stdbool.h>
#include <mem.h>

#include "UM.h"
#include "seq.h"

#define NUM_REG 8
#define HINT_SEQ_SIZE 1000
#define INSTRUCTION_LENGTH 4

static uint32_t zero = 0;
static uint64_t one = 1;

typedef struct Seg_T *Seg_T;
typedef struct Stack_T *Stack_T;

uint32_t seg_capacity;
uint32_t max_seg;
uint32_t seg_count;
uint32_t registers[NUM_REG] = { 0, 0, 0, 0, 0, 0, 0, 0 };
Seg_T    *segments;
Stack_T  available_IDs;

struct Seg_T {
        bool     is_mapped;
        unsigned length;
        uint32_t segID;
        uint32_t words[]; 
};

struct Stack_T {
        int count;
        struct elem {
                void *x;
                struct elem *link;
        } *head;
};

/***************************/
/* static helper functions */
/***************************/

/* STACK FUNCTIONS */

static inline Stack_T Stack_new(void) {
        Stack_T stk;
        NEW(stk);
        stk->count = 0;
        stk->head = NULL;
        return stk;
}

static inline int Stack_empty(Stack_T stk) {
        return stk->count == 0;
}

static inline void Stack_push(Stack_T stk, void *x) {
        struct elem *t;
        NEW(t);
        t->x = x;
        t->link = stk->head;
        stk->head = t;
        stk->count++;
}

static inline void *Stack_pop(Stack_T stk) {
        void *x;
        struct elem *t;
        t = stk->head;
        stk->head = t->link;
        stk->count--;
        x = t->x;
        FREE(t);
        return x;
}

static inline void Stack_free(Stack_T *stk) {
        struct elem *t, *u;
        for (t = (*stk)->head; t; t = u) {
                u = t->link;
                FREE(t);
        }
        FREE(*stk);
}

/* SEGMENT FUNCTIONS */

static inline Seg_T    Seg_new(int length, uint32_t segID)
{
        Seg_T segment = malloc(sizeof(*segment) + 
                               (length * sizeof(*segment->words)));
        assert(segment != NULL);

        /* set all necessary segment properties */
        segment->is_mapped = true;
        segment->length = length;
        segment->segID = segID;

        /* initalize all words to 0 */
        for (int i = 0; i < length; i++) {
                (segment->words)[i] = 0;
        }

        return segment; 
}

/* gets the word at a given index */
static inline uint32_t Seg_get_word(Seg_T segment, unsigned index)
{
        return (segment->words)[index];
}

/* sets the word at a given index */
static inline void   Seg_put_word(Seg_T segment, unsigned index, uint32_t word)
{
        (segment->words)[index] = word;
}

/* returns the length of a segment */
static inline int      Seg_length(Seg_T segment)
{
        return segment->length;
}

/* returns the segment ID */
static inline uint32_t Seg_ID(Seg_T segment)
{
        return segment->segID;
}

/* attempts to map a given segment to a certain length */
/* if segment is already mapped, returns false */
/* otherwise, returns true on success */
static inline bool     Seg_map(Seg_T segment, int length)
{

        /* if segment is already mapped */
        if (segment->is_mapped) return false;

        Seg_T new_seg = malloc(sizeof(*new_seg) + 
                               (length * sizeof(*new_seg->words)));
        assert(new_seg != NULL);
      
        /* sets segment properites and initalizes words to 0 */ 
        new_seg->is_mapped = true; 
        new_seg->length = length;
        new_seg->segID = Seg_ID(segment);        

        for (int i = 0; i < length; i++) {
                (new_seg->words)[i] = 0;
        }

        free(segment);
        segments[Seg_ID(new_seg)] = new_seg;

        return true;
}

/* flips segment to be unmapped */
static inline void     Seg_unmap(Seg_T segment)
{
        segment->is_mapped = false;
}

/* returns if segment is mapped (bool) */
static inline bool     Seg_is_mapped(Seg_T segment)
{
        return segment->is_mapped;
}

/* frees memory associated with segment */
static inline void     Seg_free(Seg_T *segment)
{
        free(*segment);
}


/*********************/
/* BITPACK FUNCTIONS */
/*********************/

static inline uint64_t shl(uint64_t word, unsigned bits)
{
        if (bits == 64) return 0;
        else return word << bits;
}

static inline uint64_t shr(uint64_t word, unsigned bits)
{
        if (bits == 64) return 0;
        else return word >> bits;
}

static inline uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb,
                      uint64_t value)
{
        unsigned hi = lsb + width; /* one beyond the most significant bit */
        return shl(shr(word, hi), hi)                 /* high part */
                | shr(shl(word, 64 - lsb), 64 - lsb)  /* low part  */
                | (value << lsb);                     /* new part  */
}

static inline uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        unsigned hi = lsb + width; /* one beyond the most significant bit */
        return shr(shl(word, 64 - hi), 64 - width); 
}

/* returns a particular segment from the sequence */
static inline Seg_T UM_get_seg(unsigned segID)
{
        return segments[segID];
}


/*******************/
/* INPUT FUNCTIONS */
/*******************/

/* returns the uint32_t value of a given input from a file */
static inline uint32_t read_instruction_line(FILE *fp)  
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


/****************/
/* UM FUNCTIONS */
/****************/

/* gets a word from a specified segment */
static inline uint32_t UM_get_segment_word(uint32_t segID, unsigned offset)
{
        return Seg_get_word(UM_get_seg(segID), offset);
}

/* sets a word value for a specified segment */
static inline void     UM_set_segment_word(uint32_t segID, 
                             unsigned offset, uint32_t word)
{
        Seg_put_word(UM_get_seg(segID), offset, word);
}

/* gets the length of a specified segment (by segID) */
static inline int      UM_get_segment_length(uint32_t segID)
{
        return Seg_length(UM_get_seg(segID));
}

static inline void UM_add_seg(Seg_T new_seg)
{
        /* if count at capacity, expand */
        if (seg_count == seg_capacity) {
                /* make new array */
                Seg_T *temp = (Seg_T *)malloc(sizeof(Seg_T) 
                                              * seg_capacity * 5);
                assert(temp);

                /* copy from old to new */
                for (unsigned i = 0; i < seg_capacity; i++) {
                        temp[i] = segments[i];
                }

                /* delete old */
                free(segments);

                /* set new to array */
                segments = temp;

                /* double capacity */
                seg_capacity = seg_capacity * 5;
        }

        /* place at max_seg */
        segments[max_seg] = new_seg; 

        /* increment max_seg */
        (seg_count)++;
        (max_seg)++;
}

/* maps a segment to specified size (num of words to hold) */
static inline uint32_t UM_map_segment(unsigned numWords)
{
        /* gets ID from stack, maps segment */
        if (Stack_empty(available_IDs) == 0) {
                uint32_t segID = 
                              (uint32_t)(uintptr_t)Stack_pop(available_IDs);
                Seg_map(UM_get_seg(segID), numWords);
                return segID;
        }

        /* need to add on new segment to sequence */
        Seg_T new_seg = Seg_new(numWords, max_seg);
        UM_add_seg(new_seg);

        return Seg_ID(new_seg);
}

/* unmaps segment, making it unusable to UM until re-map */
static inline void     UM_unmap_segment(uint32_t segID)
{
        /* unmap segment */
        Seg_unmap(UM_get_seg(segID));

        /* push segID back onto stack of available IDs */
        Stack_push(available_IDs, (void *)(uintptr_t)segID);
}

/* gets the value of a specified register */
static inline uint32_t UM_get_register(unsigned reg)
{
        return registers[reg];
}

/* sets the value of a specified register */
static inline void     UM_set_register(unsigned reg, uint32_t word)
{
        registers[reg] = word;
}


/*****************************/
/* UM Instructions           */
/*****************************/

/* moves value from one register to another if a certain register is set to 0 */
static inline void conditional_move(int rA, int rB, int rC)
{
        if (UM_get_register(rC) != 0)
                UM_set_register(rA, UM_get_register(rB));
}

/* loads a particular value from a specified segment */
/* stores value in a specified register */
static inline void segmented_load(int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(rB); 
        uint32_t rC_val = UM_get_register(rC); 
       
        UM_set_register(rA, UM_get_segment_word(rB_val, rC_val));
}

/* loads a particular value from a register */
/* stores value into a specified word in a certain segment in memory */
static inline void segmented_store(int rA, int rB, int rC)
{
        uint32_t rA_val = UM_get_register(rA); 
        uint32_t rB_val = UM_get_register(rB); 
        uint32_t rC_val = UM_get_register(rC); 
        
        UM_set_segment_word(rA_val, rB_val, rC_val);
}

/* does addition between the values stored in two registers */
static inline void addition(int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(rB); 
        uint32_t rC_val = UM_get_register(rC); 
        uint32_t sum = (rB_val + rC_val) % (one << 32);
        UM_set_register(rA, sum); 
}

/* does multiplication between values stored in two register */
static inline void multiplication(int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(rB); 
        uint32_t rC_val = UM_get_register(rC); 
        uint32_t product = (rB_val * rC_val) % (one << 32);
        UM_set_register(rA, product); 
}

/* does division between values stores in two registers */
static inline void division(int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(rB); 
        uint32_t rC_val = UM_get_register(rC);

        uint32_t quotient = (rB_val / rC_val);
        UM_set_register(rA, quotient); 
}

/* returns the result of a NAND on two values store in two registers */
static inline void bitwise_NAND(int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(rB); 
        uint32_t rC_val = UM_get_register(rC); 
        uint32_t NAND = ~(rB_val & rC_val);
        UM_set_register(rA, NAND); 
}

/* function used to signal end of computation */
/* (function doesn't actually do anything, but is used by UM to end program) */
static inline void halt(int rA, int rB, int rC)
{
        (void) rA;
        (void) rB;
        (void) rC;
}

/* maps a new segment with a given length and stores segID into a register */
static inline void map_segment(int rA, int rB, int rC)
{
        UM_set_register(rB, UM_map_segment(UM_get_register(rC)));
        (void) rA;
}

/* unmaps a specified segment (not m[0]) */
static inline void unmap_segment(int rA, int rB, int rC)
{
        int segID = UM_get_register(rC);

        UM_unmap_segment(segID);

        (void) rA;
        (void) rB;
}

/* outputs a value from a register (as long as the value is valid ASCII) */
static inline void output(int rA, int rB, int rC)
{
        uint32_t c = UM_get_register(rC);
        if (c <= 255) putchar(c);

        (void) rA;
        (void) rB;
}

/* reads in a character from input and stores it in a register */
static inline void input(int rA, int rB, int rC)
{
        char c = getchar();
        if (c == EOF) UM_set_register(rC, (~zero));
        else          UM_set_register(rC, c); 

        (void) rA;
        (void) rB;
}

/* loads the contents of a given memory segment into m[0] */
/* (instruction is suppose to move program counter to specified location */
/*  but this is instead done in the actual UM) */
static inline void load_program(int rA, int rB, int rC)
{
        /* if trying to load m[0], do nothing */
        if (UM_get_register(rB) == 0) return;

        /* get segment m[rB_val] length */
        uint32_t segID = UM_get_register(rB);
        int seg_length = UM_get_segment_length(segID);

        /* unmap m[0], re-map with new length (from m[rB_val]) */
        UM_unmap_segment(0);
        UM_map_segment(seg_length);

        /* copy contents of m[rB_val] into m[0] */
        for (int i = 0; i < seg_length; i++) {
                uint32_t word = UM_get_segment_word(segID, i);
                UM_set_segment_word(0, i, word);
        }

        (void) rA;
        (void) rC;
}

/* loads a particular value and stores it in a specified register */
static inline void load_value(int rA, int value)
{
        UM_set_register(rA, value); 
}

static void (*instructions[13]) (int rA, int rB, int rC) = {
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

/***********************/
/* interface functions */
/***********************/

/* initalizes a new UM */
/* hasn't yet stored program instructions -> see read_program() */
void    UM_new()
{
        available_IDs = Stack_new();
        max_seg = 0;
        seg_capacity = 10;
        seg_count = 0;

        segments = NULL;
}


/* reads the instructions of the given input file program */
/* stores these instructions in m[0] of the given UM */
void     UM_read_program(FILE *fp)
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
        int sequence_length = Seq_length(instructions);
        segments = (Seg_T *)malloc(sizeof(Seg_T) * seg_capacity);
        UM_map_segment(sequence_length);

        /* get each instruction from sequence, put in new segment 0 */
        for (int i = 0; i < sequence_length; i++) {
                uint32_t instruction = 
                                 (uint32_t)(uintptr_t)Seq_get(instructions, i);
                UM_set_segment_word(0, i, instruction);
        }

        /* free sequence of instructions */
        Seq_free(&instructions);
}

/* runs the program instructions until halt is called or a fail case is hit */
void     UM_run_program()
{
        uint32_t p_counter = 0;
        while (true) {
                /* get the instruction and its opcode */
                uint32_t instruction = UM_get_segment_word(0, 
                                                           p_counter);

                int op_code = Bitpack_getu(instruction, 4, 28);
                int regA = 0;
                int regB = 0;
                int regC = 0;

                /* instruction is load_value */
                if (op_code == 13) {
                        regA  = Bitpack_getu(instruction, 3, 25);
                        int value = Bitpack_getu(instruction, 25, 0);
                        load_value(regA, value);

                /* instruction is halt */
                } else if (op_code == 7) break;
                else if (op_code == 12) {
                        regB = Bitpack_getu(instruction, 3, 3);
                        instructions[op_code](regA, regB, regC);

                        regC = Bitpack_getu(instruction, 3, 0);
                        p_counter = registers[regC];

                /* all other instructions */
                } else {
                        regA = Bitpack_getu(instruction, 3, 6);
                        regB = Bitpack_getu(instruction, 3, 3);
                        regC = Bitpack_getu(instruction, 3, 0);

                        instructions[op_code](regA, regB, regC);
                }

                /* move program counter accordingly */
                if (op_code != 12) p_counter++;
        }
}

/* free associated memory for UM */
void     UM_free()
{
        /* free every segment inside sequence */
        int sequence_length = max_seg;
        for (int i = 0; i < sequence_length; i++) {
                Seg_T seg = UM_get_seg(i);
                Seg_free(&seg);
        }

        /* free whole sequence and struct */
        Stack_free(&(available_IDs));
        free(segments);
}

