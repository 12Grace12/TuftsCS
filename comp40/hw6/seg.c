/*
 * seg.c
 * by Ben Tanen and Rebecca Larson
 *
 * The implementation for the memory segment ADT
 * Includes definitions of all functions used by Seg_T
 * A memory segment is a struct containing the segments length, ID, current
 * mapping state (true or false) and an array of uint32_t words
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "assert.h"

#include "seg.h"

struct Seg_T {
        bool     is_mapped;
        unsigned length;
        uint32_t segID;
        uint32_t *words; /* change this !!!!!!!!!! */
};

/* allocates a new segment of a given length and segID */
Seg_T    Seg_new(int length, uint32_t segID)
{
        Seg_T segment = malloc(sizeof(*segment));
        assert(segment != NULL);

        /* set all necessary segment properties */
        segment->is_mapped = true;
        segment->length = length;
        segment->segID = segID;
        segment->words = (uint32_t *)malloc(sizeof(uint32_t) * length);

        /* initalize all words to 0 */
        for (int i = 0; i < length; i++) {
                (segment->words)[i] = 0;
        }

        return segment; 
}

/* gets the word at a given index */
uint32_t Seg_get_word(Seg_T segment, unsigned index)
{
        assert(segment && segment->is_mapped);
        assert(segment->length > index);
        return (segment->words)[index];
}

/* sets the word at a given index */
void     Seg_put_word(Seg_T segment, unsigned index, uint32_t word)
{
        assert(segment && segment->is_mapped);
        assert(segment->length > index);
        (segment->words)[index] = word;
}

/* returns the length of a segment */
int      Seg_length(Seg_T segment)
{
        assert(segment && segment->is_mapped);
        return segment->length;
}

/* returns the segment ID */
uint32_t Seg_ID(Seg_T segment)
{
        assert(segment && segment->is_mapped);
        return segment->segID;
}

/* attempts to map a given segment to a certain length */
/* if segment is already mapped, returns false */
/* otherwise, returns true on success */
bool     Seg_map(Seg_T segment, int length)
{
        assert(segment);

        /* if segment is already mapped */
        if (segment->is_mapped) return false;

        free(segment->words);
      
        /* sets segment properites and initalizes words to 0 */ 
        segment->is_mapped = true; 
        segment->length = length;
        segment->words = (uint32_t *)malloc(sizeof(uint32_t) * length);

        for (int i = 0; i < length; i++) {
                (segment->words)[i] = 0;
        }

        return true;
}

/* flips segment to be unmapped */
void     Seg_unmap(Seg_T segment)
{
        assert(segment);
        segment->is_mapped = false;
}

/* returns if segment is mapped (bool) */
bool     Seg_is_mapped(Seg_T segment)
{
        assert(segment);
        return segment->is_mapped;
}

/* frees memory associated with segment */
void     Seg_free(Seg_T *segment)
{
        assert(segment && *segment);
        free((*segment)->words);
        free(*segment);
}

