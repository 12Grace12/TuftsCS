/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * Main Compression / Decompression Module Implementation 
 *
 * Implementation of the main compression / decompression functions and any 
 * utilized helper functions. These functions are used by the main 40image
 * program and call on four other modules (in addition to the helper functions)
 */

#include <stdlib.h>

#include "compress40.h"
#include "arith40.h"
#include "ppm_compression_io.h"
#include "discrete_cosine.h"
#include "rgb_component_conversion.h"
#include "bitpack.h"

#include "a2methods.h"
#include "a2blocked.h"
#include "assert.h"

const int BLOCKSIZE = 2;

typedef struct {
        float sum_Pr;
        float sum_Pb;
        float y_val[4];
        int ppm_denom;
} compress_closure;

typedef struct {
        A2Methods_UArray2 img;
        A2Methods_T methods;
} copy_closure;

void    compress_pixel(int pxl_num, void *elem, void *cl);
Pnm_rgb decompress_codeword(FILE *fp, int img_denom);
void    put_rgb_pixels(Pnm_ppm img, struct Pnm_rgb *rgb_values, unsigned word);
void    trim_image(Pnm_ppm img);


/* the 'main' function of the compression process */
/* calls all necessary functions to compress image and output codewords */
void compress40(FILE *fp)
{
        /* convert file pointer to Pnm_ppm struct & pixmap */
        Pnm_ppm img = read_ppm(fp);

        /* trim image to have even width and height */
        trim_image(img);

        /* print header of compressed image */
        print_header(img->width, img->height);

        /* create struct to be passed to pseudo-mapping function */
        compress_closure cl = { .sum_Pr = 0, .sum_Pb = 0, 
                                .ppm_denom = img->denominator };

        /* calculate number of blocks in row / column */
        unsigned blocks_in_col = img->methods->width(img->pixels) / BLOCKSIZE;
        unsigned blocks_in_row = img->methods->height(img->pixels) / BLOCKSIZE;

        /* for loop through each block (in row-major order) */
        for (unsigned b_row = 0; b_row < blocks_in_row; b_row++) {
                for (unsigned b_col = 0; b_col < blocks_in_col; b_col++) {
                        for (int i = 0; i < 4; i++) {
                                /* calculate next pxl location and get it */
                                int col = (b_col * BLOCKSIZE) + (i % BLOCKSIZE);
                                int row = (b_row * BLOCKSIZE) + (i / BLOCKSIZE);
                                void *elem = img->methods->at(img->pixels, 
                                                              col, row);

                                compress_pixel(i, elem, &cl);    
                        }
                        
                }
        }
        Pnm_ppmfree(&img);
}

/* the 'main' function of the decompression process */
/* calls all necessary functions to decompress codewords and output image */
void decompress40(FILE *fp)
{
        /* read header and create ppm image based on dimensions of header */
        Pnm_ppm img = read_header(fp);

        /* loop through the codewords, decompressing them into an image */
        for (unsigned word = 0; word < (img->height * img->width) / 4; word++) {
                /* decompress codeword into 4 rgb pixel values */
                struct Pnm_rgb *rgb_values = decompress_codeword(fp, 
                                                              img->denominator);

                /* put rgb pixels into position in pixmap */
                put_rgb_pixels(img, rgb_values, word);

                /* free rgb pixel array */
                free(rgb_values);
        }

        /* print decompressed image (with pixels from codewords) to stdout */
        print_ppm(img, stdout);
        Pnm_ppmfree(&img);
}

/* compresses the rgb values of a pixel to component video values */
/* once a full block is compressed, it packs / prints a codeword */
void compress_pixel(int pxl_num, void *elem, void *cl)
{
        /* pull denominator from closure and use to convert RGB to floats */
        float denom = (*(compress_closure *)cl).ppm_denom;

        /* convert rgb (in floats) to component video format */
        float Y = rgb_to_component_Y(((Pnm_rgb)elem)->red / denom,
                                     ((Pnm_rgb)elem)->green / denom,
                                     ((Pnm_rgb)elem)->blue / denom);
        float Pb = rgb_to_component_Pb(((Pnm_rgb)elem)->red / denom, 
                                      ((Pnm_rgb)elem)->green / denom,
                                      ((Pnm_rgb)elem)->blue / denom);
        float Pr = rgb_to_component_Pr(((Pnm_rgb)elem)->red / denom, 
                                      ((Pnm_rgb)elem)->green / denom,
                                      ((Pnm_rgb)elem)->blue / denom);

        /* add Pb, Pr, and Y value to running sums / arrays of values */
        (*(compress_closure *)cl).sum_Pb += Pb;
        (*(compress_closure *)cl).sum_Pr += Pr;
        (*(compress_closure *)cl).y_val[pxl_num] = Y;

        /* when values from 4 pixels have been converted (col & row are odd) */
        if (pxl_num == 3) {

                /* calculate average values and find indicies of chroma */
                float avg_Pb = (*(compress_closure *)cl).sum_Pb / 4.0;
                float avg_Pr = (*(compress_closure *)cl).sum_Pr / 4.0;
                unsigned index_Pb = Arith40_index_of_chroma(avg_Pb);
                unsigned index_Pr = Arith40_index_of_chroma(avg_Pr);

                /* use 4 y_values in discrete cosine for a,b,c,d values */
                float *y_val = (*(compress_closure *)cl).y_val;
                uint64_t a = discr_cos_a(y_val[0], y_val[1], y_val[2],y_val[3]);
                int64_t b = discr_cos_b(y_val[0], y_val[1], y_val[2], y_val[3]);
                int64_t c = discr_cos_c(y_val[0], y_val[1], y_val[2], y_val[3]);
                int64_t d = discr_cos_d(y_val[0], y_val[1], y_val[2], y_val[3]);

                /* pack the above calculated values into a uint64_t word */
                uint64_t word = 0;
                word = Bitpack_newu(word, 6, 26, a);
                word = Bitpack_news(word, 6, 20, b);
                word = Bitpack_news(word, 6, 14, c);
                word = Bitpack_news(word, 6,  8, d);
                word = Bitpack_newu(word, 4,  4, index_Pb);
                word = Bitpack_newu(word, 4,  0, index_Pr);

                print_codeword(word);

                /* reset closure values for next block compression */
                (*(compress_closure *)cl).sum_Pb = 0;
                (*(compress_closure *)cl).sum_Pr = 0;
        }
}

/* decompress codewords to return an array of rgb pixel values */
Pnm_rgb decompress_codeword(FILE *fp, int img_denom)
{
        /* read in code word from file pointer */
        uint64_t word = read_codeword(fp);

        /* unpack values from word using bitpack */
        unsigned a = Bitpack_getu(word, 6, 26);
        int      b = Bitpack_gets(word, 6, 20);
        int      c = Bitpack_gets(word, 6, 14);
        int      d = Bitpack_gets(word, 6, 8);
        unsigned index_Pb = Bitpack_getu(word, 4, 4);
        unsigned index_Pr = Bitpack_getu(word, 4, 0);

        /* convert index of chromas back to chroma values */
        float Pb = Arith40_chroma_of_index(index_Pb);
        float Pr = Arith40_chroma_of_index(index_Pr);

        /* perform inverse cosines to get Y-values */
        float Y_val[4];
        Y_val[0] = inv_discr_cos_Y1(a, b, c, d);
        Y_val[1] = inv_discr_cos_Y2(a, b, c, d);
        Y_val[2] = inv_discr_cos_Y3(a, b, c, d);
        Y_val[3] = inv_discr_cos_Y4(a, b, c, d);

        struct Pnm_rgb *rgb_values = malloc(4*sizeof(*rgb_values));
        assert(rgb_values != NULL);

        /* use Pb/Pr & Y values to calculate scaled rgb (multiply by denom) */
        for (int i = 0; i < 4; i++) {
                rgb_values[i].red = (int)(component_to_rgb_r(Y_val[i], Pb, Pr)
                                                                   * img_denom);
                rgb_values[i].blue = (int)(component_to_rgb_b(Y_val[i], Pb, Pr) 
                                                                   * img_denom);
                rgb_values[i].green = (int)(component_to_rgb_g(Y_val[i], Pb, Pr) 
                                                                   * img_denom);
        }

        return rgb_values;
}

/* put rgb pixels into their associated locations in a pixmap */
void put_rgb_pixels(Pnm_ppm img, struct Pnm_rgb *rgb_values, unsigned word_num)
{
        /* initalize iterator, col and row values for new decompressed word */
        unsigned array_iter = 0;
        unsigned col = (word_num * BLOCKSIZE) % img->width;
        unsigned row = ((word_num * BLOCKSIZE) / img->width) * BLOCKSIZE;

        /* loop through block in row-major format */
        for (int r = 0; r < BLOCKSIZE; r++) {
                for (int c = 0; c < BLOCKSIZE; c++) {
                        /* put rgb pxls from array into UArray2 */
                        Pnm_rgb temp;
                        temp = img->methods->at(img->pixels, col + c, row + r);
                        *temp = rgb_values[array_iter];
                        array_iter++;
                }
        }
}

/* trim any image with odd height or width to have even dimensions */
void trim_image(Pnm_ppm img)
{
        unsigned new_width = img->width;
        unsigned new_height = img->height;

        /* check if width and height are already even */
        /* otherwise, store new values for trimmed image */
        if (img->width % 2 == 0 && img->height % 2 == 0) return;
        if (img->width % 2 == 1) new_width -= 1;
        if (img->height % 2 == 1) new_height -= 1;

        /* create new UArray2 with even width / height */
        A2Methods_UArray2 trimmed;
        trimmed = img->methods->new_with_blocksize(new_width, new_height, 
                                            img->methods->size(img->pixels), 2);

        /* copy values from untrimmed pixmap to trimmed using mapping fxn */
        /* replace previous pixmap with trimmed image */
        copy_closure cl;
        cl.img = trimmed;
        cl.methods = uarray2_methods_blocked;
        
        img->methods->map_default(img->pixels, copy_pixels, &cl);
        img->methods->free(&(img->pixels));
        img->pixels = trimmed;

        /* adjust values in Pnm_ppm struct */
        if (img->width % 2 == 1) img->width -= 1;
        if (img->height % 2 == 1) img->height -= 1;
}
