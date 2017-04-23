/* 
 * uarray2.h
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #2 (part a)
 *
 * This is the interface for the 2D unboxed UArray2 type. Includes all
 * relevant functions used for this abstract data type.
 */

#ifndef UARRAY2_INCLUDED
#define UARRAY2_INCLUDED

#define T UArray2_T
typedef struct T *T;

/* 
 * NOTE: For all uses of names like _new or _width, it is actually referring to
 * the full function name(s) UArray2_new and UArray2_width. This shorthand
 * is used for simplification.
 */

/* 
 * _new: given the correct dimensions (width, height, size), _new allocates
 *       a new UArray2. Returns this actual UArray2
 * _free: given a pointer to a UArray2, _free will deallocate the memory used
 *        by the passed UArray2
 */
extern T    UArray2_new(int width, int height, int size);
extern void UArray2_free(T *array);

/*
 *  _width: given a UArray2, returns width of particular UArray2
 *  _height: given a UArray2, returns height of particular UArray2
 *  _size: given a UArray2, returns size of elements stored in actual UArray2
 */
extern int  UArray2_width(T array);
extern int  UArray2_height(T array);
extern int  UArray2_size(T array);

/*
 * _at: given a UArray2 and coordinates, returns pointer to element at index 
 */
void *UArray2_at(T array, int col, int row);

/* 
 * _map_row_major: given a UArray2, a function to apply, and a client variable
 *                 pointer, returns nothing but applies the provided apply
 *                 function on each element of the UArray2 in row_major order
 * _map_col_major: given a UArray2, a function to apply, and a client variable
 *                 pointer, returns nothing but applies the provided apply
 *                 function on each element of the UArray2 in col_major order 
 */
extern void UArray2_map_row_major(T array,
            void apply(int col, int row, UArray2_T array, void *elem, void *cl),
            void *cl);
extern void UArray2_map_col_major(T array,
            void apply(int col, int row, UArray2_T array, void *elem, void *cl),
            void *cl);

#undef T
#endif
