/* 
 * uarray2b.c
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #3 (part a)
 *
 * This is the implementation for the 2D unboxed UArray2 type in a blocked form.
 * It is similar to the UArray2 from assignment #2. This file includes all
 * relevant functions used for this abstract data type and their
 * implementations.
 *
 * Each UArray2b_T type holds associated height, width, blocksize, element size
 * and a 2D UArray2_T. Each element of this UArray2 is a block, which is also a
 * UArray2_T.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "assert.h"
#include "uarray2.h"
#include "uarray2b.h"

/* in-place ceiling function */
#define ceil(a,b) (a%b==0)?(a/b):((a/b)+1)

#define T UArray2b_T
struct T {
       int height;
       int width;
       int blocksize;
       int size;
       UArray2_T blocks;
};

/* allocates a new UArray2b struct & associated inner UArray2_T / blocks */
T UArray2b_new(int height, int width, int size, int blocksize)
{
        /* make sure width / height / size / blocksize are valid */
        assert (height >= 0 && width >= 0 && size >= 0 && blocksize >= 0);

        /* initalize new struct */
        T array = malloc(sizeof(*array));

        /* store arguments in struct */
        array->height    = height;
        array->width     = width;
        array->blocksize = blocksize;
        array->size      = size;

        /* calculate number of blocks */
        /* initialize inner UArray2_T of blocks */
        int block_rows = ceil(width,blocksize);
        int block_cols = ceil(height,blocksize);
        array->blocks = UArray2_new(block_cols, block_rows, sizeof(UArray2_T));

        /* for each block, initialize as UArray2_T */
        for (int row = 0; row < block_rows; row++){
                for (int col = 0; col < block_cols; col++){
                        UArray2_T block = UArray2_new(blocksize,blocksize,size);
                        *((UArray2_T *)UArray2_at(array->blocks,
                                                  col,row)) = block;
                }
        }
        return array;
}

/* 
 * allocates a new UArray2b struct & associated inner UArray2_T / blocks
 * _new_64K_block used to allocate UArray2b with largest blocksize that fits
 * in 64kb of memory
 */
T UArray2b_new_64K_block(int width, int height, int size)
{
        /* make sure width / height / size are valid */
        assert (height >= 0 && width >= 0 && size >= 0);
        
        /* initialize new struct */
        T array = malloc(sizeof(*array));

        /* store arguments in struct */
        /* blocksize made as large as possible to fit in 64Kb of memory */
        /* found using eqn: 64kb >= blocksize * blocksize * size */
        int blocksize    = floor(sqrt((1024*64)/size));
        array->height    = height;
        array->width     = width;
        array->blocksize = blocksize;
        array->size      = size;
       
        /* calculate number of blocks */
        /* initialize inner UArray2_T of blocks */
        int block_rows = ceil(height,blocksize);
        int block_cols = ceil(width,blocksize);
        array->blocks = UArray2_new(block_cols, block_rows, sizeof(UArray2_T));

        /* for each block, initialize as UArray2_T */
        for (int row = 0; row < block_rows; row++){
                for (int col = 0; col < block_cols; col++){
                        UArray2_T block = UArray2_new(blocksize,blocksize,size);
                        *((UArray2_T *)UArray2_at(array->blocks,
                                                  col,row)) = block;
                 }
        }
        return array;
}

/* frees the memory allocated for UArray2b struct and deletes */
void UArray2b_free (T *array2b)
{
        /* make sure not passed NULL T */
        assert(array2b && *array2b);

        /* calculate variables used for block indexing */
        int block_rows = ceil((*array2b)->height,(*array2b)->blocksize);
        int block_cols = ceil((*array2b)->width,(*array2b)->blocksize);

        /* free each individual inner block with _free */
        for (int row = 0; row < block_rows; row++){
                for (int col = 0; col < block_cols; col++){
                        UArray2_free(UArray2_at((*array2b)->blocks,col,row));
                }
        }

        /* free UArray2 of blocks and entire struct */
        UArray2_free(&((*array2b)->blocks));
        free(*array2b);
}

/* returns width of passed array */
int UArray2b_width (T array2b)
{
        /* make sure not passed NULL T */
        assert(array2b);

        return array2b->width;
}

/* returns height of passed array */
int UArray2b_height(T array2b)
{
        /* make sure not passed NULL T */
        assert(array2b);

        return array2b->height;
}

/* returns element size of passed array */
int UArray2b_size (T array2b)
{
        /* make sure not passed NULL T */
        assert(array2b);

        return array2b->size;
}

/* returns blocksize of passed array */
int UArray2b_blocksize(T array2b)
{
        /* make sure not passed NULL T */
        assert(array2b);

        return array2b->blocksize;
}

/* given an array and an index, returns pointer to the element at index */
void *UArray2b_at(T array2b, int col, int row)
{
        /* make sure not passed NULL T */
        assert(array2b);

        /* makes sure passed index is in valid range */
        assert(col >= 0 && col < array2b->width &&
               row >= 0 && row < array2b->height);

        /* determines coordinates of block and element within block */
        int block_col = col / array2b->blocksize;
        int block_row = row / array2b->blocksize;
        int col_in_block = col % array2b->blocksize;
        int row_in_block = row % array2b->blocksize;

        /* accesses block containing element */
        UArray2_T block = *((UArray2_T *)UArray2_at(array2b->blocks,
                                                    block_col,block_row));

        /* returns actual element pointer in block */
        return UArray2_at(block,col_in_block,row_in_block);  
}

/* 
 * given a UArray2b_T, a block (UArray2_T), apply function, a closure, and 
 * the coordinates of the block in outer_array, applies given function on all
 * elements contained within block in row-major order
 * NOTE: this is a helper function used by UArray2b_map
 */
void UArray2b_map_block(T outer_array, UArray2_T inner_block,
        void apply(int col, int row, UArray2b_T array, void *elem, void *cl),
        void *cl, int b_col, int b_row)
{
        /* gets blocksize from outer UArray2b */
        int blocksize = outer_array->blocksize;

        /* for loop through each coordinate in row_major order */
        for (int row=0; row < UArray2_height(inner_block); row++) {
                for (int col=0; col < UArray2_width(inner_block); col++) {
                        /* calculates column and row of elem in whole array */
                        /* uses formula: (blocksize * col_of_block) + col */
                        int out_col = (blocksize * b_col) + col;
                        int out_row = (blocksize * b_row) + row;

                        /* makes sure not attempting to access elem outside */
                        /* bounds of UArray2b (in uninitialized space) */
                        if (out_col < outer_array->width && 
                            out_row < outer_array->height) {
                                /* apply apply-function to each element */
                                void *elem_pt = UArray2_at(inner_block,col,row);
                                apply(out_col,out_row,outer_array,elem_pt,cl);
                        }
                }
        }

        return;
}

/*
 * given a UArray2b_T, applies given function pointer to all elements in
 * block-major order (row-major order within blocks).
 */
void UArray2b_map(T array2b,
                  void apply(int i, int j, T array2b, void *elem, void *cl),
                  void *cl)
{
        /* make sure not passed NULL T */
        assert(array2b);

        /* calculate variables used for block indexing */
        int block_rows = ceil(array2b->height,array2b->blocksize);
        int block_cols = ceil(array2b->width,array2b->blocksize);

        /* go through each block in row-major order */
        for (int row = 0; row < block_rows; row++) {
                for (int col = 0; col < block_cols; col++) {
                        /* access particular block and pass to helper fxn */
                        UArray2_T block; 
                        block = *((UArray2_T *)UArray2_at(array2b->blocks,
                                                          col,row));
                        UArray2b_map_block(array2b,block,apply,cl,col,row);
                }
        }
}
