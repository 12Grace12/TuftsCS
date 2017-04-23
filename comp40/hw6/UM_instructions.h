/*
 * UM_instructions.h
 * by Ben Tanen and Rebecca Larson
 *
 * The interface for the UM instruction set
 * Includes declarations of all functions associated with UM instructions
 */

#ifndef UM_INSTRUCTIONS_INCLUDED
#define UM_INSTRUCTIONS_INCLUDED

#include "UM.h"
   
void conditional_move(UM_T UM, int rA, int rB, int rC);
void segmented_load(UM_T UM, int rA, int rB, int rC);
void segmented_store(UM_T UM, int rA, int rB, int rC);
void addition(UM_T UM, int rA, int rB, int rC);
void multiplication(UM_T UM, int rA, int rB, int rC);
void division(UM_T UM, int rA, int rB, int rC);
void bitwise_NAND(UM_T UM, int rA, int rB, int rC);
void halt(UM_T UM, int rA, int rB, int rC);
void map_segment(UM_T UM, int rA, int rB, int rC);
void unmap_segment(UM_T UM, int rA, int rB, int rC);
void output(UM_T UM, int rA, int rB, int rC);
void input(UM_T UM, int rA, int rB, int rC);
void load_program(UM_T UM, int rA, int rB, int rC);
void load_value(UM_T UM, int rA, int value);

#endif
