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

typedef struct UM_T *UM_T;

UM_T     UM_new();
uint32_t UM_get_segment_word(UM_T UM, uint32_t segID, unsigned offset);
void     UM_set_segment_word(UM_T UM, uint32_t segID, 
                             unsigned offset, uint32_t word);
int      UM_get_segment_length(UM_T UM, uint32_t segID);
uint32_t UM_map_segment(UM_T UM, unsigned numWords); 
void     UM_unmap_segment(UM_T UM, uint32_t segID);
uint32_t UM_get_register(UM_T UM, unsigned reg);
void     UM_set_register(UM_T UM, unsigned reg, uint32_t word);
void     UM_read_program(UM_T UM, FILE *fp);
void     UM_run_program(UM_T UM); 
void     UM_free(UM_T *UM);

#undef T
#endif
