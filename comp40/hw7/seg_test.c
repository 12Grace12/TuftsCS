/*
 * seg_test.c
 * by Ben Tanen and Rebecca Larson
 *
 * File used to test functionality of the memory segment ADT
 * Includes tests for putting / getting, mapping, and returning properties
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "seg.h"

void seg_put_get_test();
void seg_mapping_test();
void seg_map_mapped_test();
void set_properites_test();

int main() 
{
        /* runs tests to see if any fail */
        seg_put_get_test();
        seg_mapping_test();
        seg_map_mapped_test();
        set_properites_test();
        return 0;
}

/* puts and gets a value to make sure they are equal */
void seg_put_get_test()
{
        uint32_t SegID = 1;
        uint32_t input = 6;
        uint32_t output;
        
        Seg_T segment = Seg_new(5, SegID);
        Seg_put_word(segment, 2, input);
        output = Seg_get_word(segment, 2);

        if (output != input) fprintf(stdout, "you failed the put/get test!!\n");
        
        Seg_free(&segment);
}

/* maps, unmaps, then remaps a segment to check mapping process */
void seg_mapping_test()
{
        uint32_t SegID = 1;
        int length = 5;
        bool failed = false;        

        Seg_T segment = Seg_new(length, SegID);
        if (!Seg_is_mapped(segment)) failed = true;
        Seg_unmap(segment);
        if (Seg_is_mapped(segment)) failed = true;
        Seg_map(segment, length);
        if (!Seg_is_mapped(segment)) failed = true;

        Seg_free(&segment);

        if (failed) fprintf(stdout, "you failed the mapping test!\n");
        
}

/* checks if mapping an already mapped segment returns FALSE from Seg_map */
void seg_map_mapped_test()
{ 
        uint32_t SegID = 1;
        int length = 5;
        bool failed = false;        

        Seg_T segment = Seg_new(length, SegID);
        if (Seg_map(segment, length)) failed = true;
        
        Seg_free(&segment);

        if (failed) fprintf(stdout, "you failed the mapping a mapped test!\n");
}

/* tests if returning a segments properties works */
void set_properites_test()
{
        uint32_t SegID = 1;
        bool failed = false;
        int length1 = 5;
        int length2 = 10;

        Seg_T segment = Seg_new(length1, SegID);
        if (length1 != Seg_length(segment) || SegID != Seg_ID(segment)) {
                failed = true;
        }

        Seg_unmap(segment);
        Seg_map(segment, length2);

        if (length2 != Seg_length(segment) || SegID != Seg_ID(segment)) {
                failed = true;
        }

        Seg_free(&segment);

        if (failed) fprintf(stdout, "you failed the properties test!\n");
}
