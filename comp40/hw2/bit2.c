/* 
 * bit2.c
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #2 (part b)
 *
 * This is the implementation for the 2D bit array Bit2 type. Includes all
 * relevant functions used for this abstract data type and their
 * implementations.
 *
 * Each Bit2_T type holds associated height, width, length and
 * a 1D Hanson bit vector. Each element of the 2D Bit array is mapped to an 
 * index of the 1D bit vector.
 */

#include <stdlib.h>
#include <stdio.h>
#include "bit2.h"
#include "bit.h"
#include "except.h"

#define T Bit2_T
struct T {
        int height;
        int width;
        int length;
        Bit_T bits;
};

/* allocates a new 2D Bit array (and associated struct) */
T Bit2_new(int width, int height)
{
        /* make sure width / height are non-negative */
        if (width < 0 || height < 0) {
                Except_T Allocation_Failure = { "Memory Alloc Failure" };
                RAISE(Allocation_Failure);
        }
        
        /* initialize new Bit2 struct */
        T array = malloc(sizeof(*array));

        /* store arguments in struct */
        array->height = height;
        array->width = width;
        array->length = height * width;

        /* create array of correct size */
        array->bits = Bit_new(array->length);
        return array;
}

/* frees the memory allocated for Bit2 struct and deletes */
void Bit2_free(T *array)
{
        /* free contained 1D Bit vector */
        Bit_free(&((*array)->bits));

        /* free entire struct */
        free(*array);
        return;
}

/* returns width of passed array */
int  Bit2_width(T array)
{
        return array->width;
}

/* returns height of passed array */
int  Bit2_height(T array)
{
        return array->height;
}

/* 
 * because of implementation of Bit2 as one 1D Bit vector,
 * this function is used to correctly map 2D indicies (ex: 3,2) to the correct
 * 1D index. Formula uses "2D" array's width to convert
 */
int index2D_to_1D(int col, int row, int width)
{
        return row * width + col; 
}


/* given an array and coordinates, returns value of bit at coordinate */ 
int Bit2_get(T array, int col, int row)
{
        /* attempts to index outside of bounds */
        if (row > array->height || row < 0 || col > array->width || col < 0) {
                Except_T Bounds_Failure = { "Out of Bounds Reference" };
                RAISE(Bounds_Failure);
        }

        /* convert 2D index to 1D, figure out correct elem to return */
        int index = index2D_to_1D(col, row, array->width);
        return Bit_get(array->bits, index); 
}

/*
 * given an array, coordinates and value, changes value of bit at
 * coordinate and returns value previously held by bit
 */
int Bit2_put(T array, int col, int row, int new_value)
{
        /* attempts to index outside of bounds */
        if (row > array->height || row < 0 || col > array->width || col < 0) {
                Except_T Bounds_Failure = { "Out of Bounds Reference" };
                RAISE(Bounds_Failure);
        } else if (new_value != 0 && new_value != 1) {
                Except_T Bit_Value_Failure = { "Invalid Bit Value" };
                RAISE(Bit_Value_Failure);
        }

        /* convert 2D index to 1D, figure out correct elem to return */
        int index = index2D_to_1D(col, row, array->width);
        return Bit_put(array->bits, index, new_value); 
}

/*
 * given a Bit2 array, a function to apply, and a client
 * variable pointer, returns nothing but applies the provided
 * apply function on each bit of the Bit2 in row_major order
 */ 
void Bit2_map_row_major(T array,
            void apply(int col, int row, Bit2_T array, int bit_val, void *cl),
            void *cl)
{
        /* for loop through each coordinate in row_major order */
        for (int row=0; row<array->height; row++) {
                for (int col=0; col<array->width; col++) {
                        int index1D = index2D_to_1D(col,row,array->width);
                        int bit_val = Bit_get(array->bits,index1D);

                        /* apply apply-function to each coordinate / element */
                        apply(col,row,array,bit_val,cl);
                }
        }

        return;
}

/*
 * given a Bit2 array, a function to apply, and a client
 * variable pointer, returns nothing but applies the provided
 * apply function on each bit of the Bit2 in col_major order
 */ 
void Bit2_map_col_major(T array,
            void apply(int col, int row, Bit2_T array, int bit_val, void *cl),
            void *cl)
{
        /* for loop through each coordinate in row_major order */
        for (int col=0; col<array->width; col++) {
                for (int row=0; row<array->height; row++) {
                        int index1D = index2D_to_1D(col,row,array->width);
                        int bit_val = Bit_get(array->bits,index1D);

                        /* apply apply-function to each coordinate / element */
                        apply(col,row,array,bit_val,cl);  
                }
        }

        return;
}
