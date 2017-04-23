/*
 * UM_instructions.c
 * by Ben Tanen and Rebecca Larson
 *
 * The implementation for the UM instruction set
 * Includes definitions of all functions associated with UM instructions
 * Each function is called by UM, and implementation of these functions
 * call back on the UM to perform different tasks associated with the memory
 * segments and the 8 registers.
 */

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"

#include "UM.h"
#include "UM_instructions.h"

static uint32_t zero = 0;
static uint64_t one = 1;

/* moves value from one register to another if a certain register is set to 0 */
void conditional_move(UM_T UM, int rA, int rB, int rC)
{
        if (UM_get_register(UM, rC) != 0)
                UM_set_register(UM, rA, UM_get_register(UM, rB));
}

/* loads a particular value from a specified segment */
/* stores value in a specified register */
void segmented_load(UM_T UM, int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(UM, rB); 
        uint32_t rC_val = UM_get_register(UM, rC); 
       
        UM_set_register(UM, rA, UM_get_segment_word(UM, rB_val, rC_val));
}

/* loads a particular value from a register */
/* stores value into a specified word in a certain segment in memory */
void segmented_store(UM_T UM, int rA, int rB, int rC)
{
        uint32_t rA_val = UM_get_register(UM, rA); 
        uint32_t rB_val = UM_get_register(UM, rB); 
        uint32_t rC_val = UM_get_register(UM, rC); 
        
        UM_set_segment_word(UM, rA_val, rB_val, rC_val);
}

/* does addition between the values stored in two registers */
void addition(UM_T UM, int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(UM, rB); 
        uint32_t rC_val = UM_get_register(UM, rC); 
        uint32_t sum = (rB_val + rC_val) % (one << 32);
        UM_set_register(UM, rA, sum); 
}

/* does multiplication between values stored in two register */
void multiplication(UM_T UM, int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(UM, rB); 
        uint32_t rC_val = UM_get_register(UM, rC); 
        uint32_t product = (rB_val * rC_val) % (one << 32);
        UM_set_register(UM, rA, product); 
}

/* does division between values stores in two registers */
void division(UM_T UM, int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(UM, rB); 
        uint32_t rC_val = UM_get_register(UM, rC);

        /* makes sure division is valid (not dividing by 0) */
        assert(rC_val != 0);
 
        uint32_t quotient = (rB_val / rC_val);
        UM_set_register(UM, rA, quotient); 
}

/* returns the result of a NAND on two values store in two registers */
void bitwise_NAND(UM_T UM, int rA, int rB, int rC)
{
        uint32_t rB_val = UM_get_register(UM, rB); 
        uint32_t rC_val = UM_get_register(UM, rC); 
        uint32_t NAND = ~(rB_val & rC_val);
        UM_set_register(UM, rA, NAND); 
}

/* function used to signal end of computation */
/* (function doesn't actually do anything, but is used by UM to end program) */
void halt(UM_T UM, int rA, int rB, int rC)
{
        (void) UM;
        (void) rA;
        (void) rB;
        (void) rC;
}

/* maps a new segment with a given length and stores segID into a register */
void map_segment(UM_T UM, int rA, int rB, int rC)
{
        UM_set_register(UM, rB, UM_map_segment(UM, UM_get_register(UM, rC)));
        (void) rA;
}

/* unmaps a specified segment (not m[0]) */
void unmap_segment(UM_T UM, int rA, int rB, int rC)
{
        int segID = UM_get_register(UM, rC);

        /* makes sure user isn't unmapping m[0] */        
        assert(segID != 0);
 
        UM_unmap_segment(UM, segID);

        (void) rA;
        (void) rB;
}

/* outputs a value from a register (as long as the value is valid ASCII) */
void output(UM_T UM, int rA, int rB, int rC)
{
        uint32_t c = UM_get_register(UM, rC);
        if (c <= 255) putchar(c);

        (void) rA;
        (void) rB;
}

/* reads in a character from input and stores it in a register */
void input(UM_T UM, int rA, int rB, int rC)
{
        char c = getchar();
        if (c == EOF) UM_set_register(UM, rC, (~zero));
        else          UM_set_register(UM, rC, c); 

        (void) rA;
        (void) rB;
}

/* loads the contents of a given memory segment into m[0] */
/* (instruction is suppose to move program counter to specified location */
/*  but this is instead done in the actual UM) */
void load_program(UM_T UM, int rA, int rB, int rC)
{
        /* if trying to load m[0], do nothing */
        if (UM_get_register(UM, rB) == 0) return;

        /* get segment m[rB_val] length */
        uint32_t segID = UM_get_register(UM, rB);
        int seg_length = UM_get_segment_length(UM, segID);

        /* unmap m[0], re-map with new length (from m[rB_val]) */
        UM_unmap_segment(UM, 0);
        UM_map_segment(UM, seg_length);

        /* copy contents of m[rB_val] into m[0] */
        for (int i = 0; i < seg_length; i++) {
                uint32_t word = UM_get_segment_word(UM, segID, i);
                UM_set_segment_word(UM, 0, i, word);
        }

        (void) rA;
        (void) rC;
}

/* loads a particular value and stores it in a specified register */
void load_value(UM_T UM, int rA, int value)
{
       UM_set_register(UM, rA, value); 
}

