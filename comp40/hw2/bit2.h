/* 
 * bit2.h
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #2 (part b)
 *
 * This is the interface for the 2D Bit2 bit array type. Includes all
 * relevant functions used for this abstract data type.
 */

#ifndef BIT2_INCLUDED
#define BIT2_INCLUDED

#define T Bit2_T
typedef struct T *T;

/* 
 * NOTE: For all uses of names like _new or _width, it is actually referring to
 * the full function name(s) Bit2_new and Bit2_width. This shorthand
 * is used for simplification.
 */

/* 
 * _new: given the correct dimensions (width, height, size), _new allocates
 *       a new Bit2. Returns this actual Bit2
 * _free: given a pointer to a Bit2, _free will deallocate the memory used
 *        by the passed Bit2
 */
extern T    Bit2_new(int width, int height);
extern void Bit2_free(T *array);

/*
 * _width: given a Bit2, returns width of particular Bit2
 * _height: given a Bit2, returns height of particular Bit2
 */
extern int  Bit2_width(T array);
extern int  Bit2_height(T array);

/*
 * _get: given an array and coordinates, returns value of bit at coordinate 
 * _put: given an array, coordinates and value, changes value of bit at
 *       coordinate and returns value previously held by bit
 */
int Bit2_get(T array, int col, int row);
int Bit2_put(T array, int col, int row, int new_value);

/* 
 * _map_row_major: given a Bit2 array, a function to apply, and a client
 *                 variable pointer, returns nothing but applies the provided
 *                 apply function on each bit of the Bit2 in row_major order
 * _map_col_major: given a Bit2 array, a function to apply, and a client
 *                 variable pointer, returns nothing but applies the provided
 *                 apply function on each bit of the Bit2 in col_major order 
 */
extern void Bit2_map_row_major(T array,
            void apply(int col, int row, Bit2_T array, int bit, void *p1),
            void *cl);
extern void Bit2_map_col_major(T array,
            void apply(int col, int row, Bit2_T array, int bit, void *p1),
            void *cl);

#undef T
#endif
