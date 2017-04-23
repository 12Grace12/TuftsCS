/*
 * UM.h
 * by Ben Tanen and Rebecca Larson
 *
 * The interface for the universal machine (UM)
 * Includes declarations of all functions used by UM_T
 */

#ifndef UM_INCLUDED
#define UM_INCLUDED

#include <inttypes.h>

void     UM_new();
void     UM_read_program(FILE *fp);
void     UM_run_program(); 
void     UM_free();

#undef T
#endif
