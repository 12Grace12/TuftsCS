/* 
 * a2plain.c
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #3 (part b)
 *
 * This is the implementation for the a2methods suite using a UArray2. Each of
 * its functions calls the corresponding function in UArray2.c.
 * Used for unblocked pixmap implementations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <a2plain.h>
#include "uarray2.h"

/* private abbreviation */
/* type def apply function */
typedef A2Methods_UArray2 A2;
typedef void apply_fxn(int i, int j, UArray2_T array2, void *elem, void *cl);

/* returns a 2D array with the given dimensions and element size*/
static A2 new(int width, int height, int size) 
{
        return UArray2_new(width, height, size);
}

/* returns a 2D array with the given dimensions and element size*/
/* ignores block size because UArray2 is an unblocked array */
static A2 new_with_blocksize(int width, int height, int size,
                                            int blocksize)
{
        (void) blocksize;
        return UArray2_new(width, height, size);
}

/* frees memory stored in 2D array stored at the passed pointer*/
static void a2free(A2 * array2p)
{
        UArray2_free((UArray2_T *) array2p);
}

/* returns the width of the passed 2D array */
static int width(A2 array2)
{
        return UArray2_width(array2);
}

/* returns the height of the passed 2D array */
static int height(A2 array2)
{
        return UArray2_height(array2);
}


/* returns the size of the elements stored in the passed 2D array */
static int size(A2 array2)
{
        return UArray2_size(array2);
}


/* returns 0 because the passed 2D array should be unblocked */
static int blocksize(A2 array2)
{
        (void) array2;
        return 0;
}

/* returns a pointer to the element stored at the given index in the array*/
static A2Methods_Object *at(A2 array2, int i, int j)
{
        return UArray2_at(array2, i, j);
}

/* applies the passed function to all elements in the array in row-major order*/
static void map_row_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
        UArray2_map_row_major(array2, (apply_fxn *) apply, cl);
}


/* applies the passed function to all elements in the array in col-major order*/
static void map_col_major(A2 array2, A2Methods_applyfun apply, void *cl)
{
        UArray2_map_col_major(array2, (apply_fxn *) apply, cl);
}

/* closure used for small-mapping */
struct small_closure {
        A2Methods_smallapplyfun *apply;
        void *cl;
};

/* inner function used for small-mapping */
static void apply_small(int i, int j, UArray2_T array2, void *elem, void *vcl)
{
        struct small_closure *cl = vcl;
        (void)i;
        (void)j;
        (void)array2;
        cl->apply(elem, cl->cl);
}

/* outer function used for small-mapping in row-major order */ 
static void small_map_row_major(A2 array2, A2Methods_smallapplyfun apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_row_major(array2, apply_small, &mycl);
}


/* outer function used for small-mapping in col-major order */ 
static void small_map_col_major(A2 array2, A2Methods_smallapplyfun apply,
                                void *cl)
{
        struct small_closure mycl = { apply, cl };
        UArray2_map_col_major(array2, apply_small, &mycl);
}

/* private struct containing pointers to functions*/
static struct A2Methods_T uarray2_methods_plain_struct = {
        new,
        new_with_blocksize,
        a2free,
        width,
        height,
        size,
        blocksize,
        at,
        map_row_major,         // map_row_major
        map_col_major,         // map_col_major
        NULL,                  // map_block_major
        map_row_major,         // map_default
        small_map_row_major,   // small_map_row_major
        small_map_col_major,   // small_map_col_major
        NULL,                  // small_map_block_major
        small_map_row_major    // small_map_default
};

/* exported pointer to the struct*/
A2Methods_T uarray2_methods_plain = &uarray2_methods_plain_struct;

