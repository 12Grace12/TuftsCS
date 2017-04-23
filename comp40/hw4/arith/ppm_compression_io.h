/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * PPM Compression Input/Output Module Interface
 *
 * Interface for ppm_compression_io module, which is used for input and 
 * output in compress40.
 */

#ifndef PPM_COMPRESSION_IO_INCLUDED
#define PPM_COMPRESSION_IO_INCLUDED

#include <stdint.h>
#include "pnm.h"

/* these functions are used for reading in information from input */
Pnm_ppm  read_ppm(FILE *fp);
Pnm_ppm  read_header(FILE *fp);
uint64_t read_codeword(FILE *fp);

/* these functions are used for printing information to output */
void     print_header(unsigned width, unsigned height);
void     print_codeword(uint64_t word);
void     print_ppm(Pnm_ppm img, FILE *fp);

/* this function is used for copy pixels from one Pnm_ppm to another */
void     copy_pixels(int col, int row, A2Methods_UArray2 array2, 
                     void *elem, void *cl);

#endif

