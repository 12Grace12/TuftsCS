/* 
 * uarray.c
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #2 (part a)
 *
 * This is the implementation for the 2D unboxed UArray2 type. Includes all
 * relevant functions used for this abstract data type and their
 * implementations.
 *
 * Each UArray2_T type holds associated height, width, length, element size and
 * a 1D Hanson UArray_T. Each element of 2D UArray is mapped to an index of the
 * 1D UArray.
 */

#include <stdlib.h>
#include <stdio.h>
#include "uarray2.h"
#include "uarray.h"
#include "except.h"

#define T UArray2_T
struct T {
        int height;
        int width;
        int length;
        int size;
        UArray_T elems;
};

/* allocates a new UArray2 struct (and associated 1D UArray) */
T UArray2_new(int width, int height, int size)
{
        /* make sure width / height / size are non-negative */
        if (width < 0 || height < 0 || size < 0) {
                Except_T Allocation_Failure = { "Memory Alloc Failure" };
                RAISE(Allocation_Failure);
        }
        
        /* initialize new UArray2 */
        T array = malloc(sizeof(*array));

        /* store arguments in struct */
        array->height = height;
        array->width = width;
        array->length = height * width;
        array->size = size;

        /* create array of correct size */
        array->elems = UArray_new(array->length, array->size);
        return array;
}

/* frees the memory allocated for UArray2 struct and deletes */
void UArray2_free(T *array)
{
        /* free contained 1D UArray */
        UArray_free(&((*array)->elems));

        /* free entire struct */
        free(*array);
        return;
}

/* returns width of passed array */
int  UArray2_width(T array)
{
        return array->width;
}

/* returns height of passed array */
int  UArray2_height(T array)
{
        return array->height;
}

/* returns size of elements in passed array */
int  UArray2_size(T array)
{
        return array->size;
}

/* 
 * because of implementation of UArray2 as one 1D UArray,
 * this function is used to correctly map 2D indicies (ex: 3,2) to the correct
 * 1D index. Formula uses "2D" array's width to convert
 */
int index2D_to_1D(int col, int row, int width)
{
        return row * width + col; 
}

/* 
 * given an array and a 2D index, returns the pointer to the element at said
 * index
 */
void *UArray2_at(T array, int col, int row)
{
        /* attempts to index outside of bounds */
        if (row > array->height || row < 0 || col > array->width || col < 0) {
                Except_T Bounds_Failure = { "Out of Bounds Reference" };
                RAISE(Bounds_Failure);
        }

        /* convert 2D index to 1D, figure out correct elem to return */
        int index = index2D_to_1D(col, row, array->width);
        return UArray_at(array->elems, index);
}

/*
 * given a UArray2, a function to apply, and a client
 * variable pointer, returns nothing but applies the provided
 * apply function on each element of the UArray2 in row_major order
 */ 
void UArray2_map_row_major(T array,
            void apply(int col, int row, UArray2_T array, void *elem, void *cl),
            void *cl)
{
        /* for loop through each coordinate in row_major order */
        for (int row=0; row<array->height; row++) {
                for (int col=0; col<array->width; col++) {
                        int index1D = index2D_to_1D(col,row,array->width);
                        void *elem_pt = UArray_at(array->elems,index1D);

                        /* apply apply-function to each coordinate / element */
                        apply(col,row,array,elem_pt,cl);
                }
        }

        return;
}

/*
 * given a UArray2, a function to apply, and a client
 * variable pointer, returns nothing but applies the provided
 * apply function on each element of the UArray2 in col_major order
 */ 
void UArray2_map_col_major(T array,
            void apply(int col, int row, UArray2_T array, void *elem, void *cl),
            void *cl)
{
        /* for loop through each coordinate in row_major order */
        for (int col=0; col<array->width; col++) {
                for (int row=0; row<array->height; row++) {
                        int index1D = index2D_to_1D(col,row,array->width);
                        void *elem_pt = UArray_at(array->elems,index1D);

                        /* apply apply-function to each coordinate / element */
                        apply(col,row,array,elem_pt,cl);  
                }
        }

        return;
}
