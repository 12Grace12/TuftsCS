/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * PPM Compression Input/Output Module Implementation
 *
 * Implementation for ppm_compression_io module, which is used for input and 
 * output in compress40. Many of these functions make use of the pnm_ppm 
 * interface and use the A2Methods interface to access blocked 2D arrays in 
 * in order to store images.
 */

#include "ppm_compression_io.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "a2methods.h"
#include "a2blocked.h"
#include "bitpack.h"

typedef struct {
        A2Methods_UArray2 img;
        A2Methods_T methods;
} copy_closure;

const int new_img_denom = 255;

/* copies image from file into blocked 2D UArray */
Pnm_ppm read_ppm(FILE *fp)
{
        A2Methods_T methods = uarray2_methods_blocked;
        assert(fp != NULL && methods != NULL);

        /* use Pnm_ppmread to read file and store in new 2D UArray */
        /* function returns Pnm_ppm with unknown block size (close to 64Kb) */
        Pnm_ppm img = Pnm_ppmread(fp, methods);

        /* declare new blocked UArray2 with known block-size of 2 */
        A2Methods_UArray2 blocked_pxls;
        blocked_pxls = methods->new_with_blocksize(img->width, img->height, 
                                           img->methods->size(img->pixels), 2);

        /* copies contents of original pixmap to new blocked pixmap */
        copy_closure cl;
        cl.img = blocked_pxls;
        cl.methods = methods;

        img->methods->map_default(img->pixels, copy_pixels, &cl);
        img->methods->free(&(img->pixels));
        img->pixels = blocked_pxls;

        return img;
}

/* reads a compressed image header and returns Pnm_ppm for  decompressed img */
Pnm_ppm read_header(FILE *fp)
{
        /* use provided code to read in width and height of image */
        unsigned height, width;
        int read = fscanf(fp, "COMP40 Compressed image format 2\n%u%u", 
                          &width, &height);
        assert(read == 2);
        int c = getc(fp);
        assert(c == '\n');

        A2Methods_T methods = uarray2_methods_blocked;

        /* using dimensions, make new Pnm_ppm to decompress into */
        Pnm_ppm pixmap = malloc(sizeof(*pixmap));
        pixmap->width = width;
        pixmap->height = height;
        pixmap->denominator = new_img_denom;
        pixmap->methods = methods;
        pixmap->pixels = methods->new(width, height, new_img_denom);
        
        return pixmap;
}

/* reads in codeword from file pointer and returns uint64_t word */
uint64_t read_codeword(FILE *fp)
{
        /* create new uint64_t and store values from input */
        uint64_t word = 0;

        /* loops through lsb values for four 8-bit values (in 32-bit word) */
        for (int i = 24; i >= 0; i -= 8) {
                        unsigned char c = getc(fp);
                word = Bitpack_newu(word, 8, i, c);
        }
        return word;
}

/* prints compressed image header with width / height */
void    print_header(unsigned width, unsigned height)
{
        printf("COMP40 Compressed image format 2\n%u %u\n", width, height);
}

/* prints a codeword in 4 characters */
void    print_codeword(uint64_t word)
{
        /* loops through lsb values for four 8-bit values (in 32-bit word) */
        for (int i = 24; i >= 0; i -= 8) putchar(Bitpack_getu(word, 8, i));
}

/* prints the contents of a Pnm_ppm image */
void    print_ppm(Pnm_ppm img, FILE *fp)
{
        Pnm_ppmwrite(fp, img);
}

/* mapping function used to copy pixels from passed UArray2 to a */
/* to a UArray2 stored in copy closure */
void copy_pixels(int col, int row, A2Methods_UArray2 array2, 
                 void *elem, void *cl)
{
        A2Methods_T methods = (*(copy_closure *)cl).methods;

        /* makes sure pixel to be copied is within correct bounds */
        if (col >= methods->width((*(copy_closure *)cl).img) || 
            row >= methods->height((*(copy_closure *)cl).img)) return;

        /* copies from old image to new image */
        *((Pnm_rgb)methods->at((*(copy_closure *)cl).img, col, row)) 
                                                             = *((Pnm_rgb)elem);
                                                     
        (void) array2;
}
        
