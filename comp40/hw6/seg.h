/*
 * seg.h
 * by Ben Tanen and Rebecca Larson
 *
 * The interface for the memory segment ADT
 * Includes declarations of all functions used by Seg_T
 */

#ifndef SEG_INCLUDED
#define SEG_INCLUDED

#include <inttypes.h>
#include <stdbool.h>

typedef struct Seg_T *Seg_T;

Seg_T    Seg_new(int length, uint32_t segID);
uint32_t Seg_get_word(Seg_T segment, unsigned index);
void     Seg_put_word(Seg_T segment, unsigned index, uint32_t word);
int      Seg_length(Seg_T segment);
uint32_t Seg_ID(Seg_T segment);
bool     Seg_map(Seg_T segment, int length);
void     Seg_unmap(Seg_T segment);
bool     Seg_is_mapped(Seg_T segment);
void     Seg_free(Seg_T *segment);

#undef T
#endif
