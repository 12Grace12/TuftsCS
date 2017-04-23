#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "math.h"
#include "pnm.h"
#include "a2methods.h"
#include "a2plain.h"

float calculate_ppm_diff(A2Methods_T methods, Pnm_ppm imgA, Pnm_ppm imgB);
float sum_rgb_values(void *pixelA, void *pixelB);

int main(int argc, char const *argv[])
{
        (void) argc;

        A2Methods_T methods = uarray2_methods_plain;
        /* reading in */
        /* either from file name or stdin */

        /* declare two new FILE and Pnm_ppms */
        /* FILE set to NULL in case user passed more than 2 arguments */
        FILE *imgA_fp = NULL;
        FILE *imgB_fp = NULL;
        Pnm_ppm imgA;
        Pnm_ppm imgB;

        /* check first image file */
        /* pass file binary from stdin */
        if (*argv[1] == '-') {
                imgA_fp = stdin;

        /* pass filename from command line */
        } else {
                imgA_fp = fopen(argv[1],"rb");
        }

        if (*argv[1] != '-' && *argv[2] == '-') {
                imgB_fp = stdin;
        } else if (*argv[2] == '-') {
                fprintf(stderr,"both files can't be stdin\n");
                return EXIT_FAILURE;
        } else {
                imgB_fp = fopen(argv[2],"rb");
        }

        /* checks that img is not NULL */
        /* would be NULL if fopen failed */
        assert(imgA_fp && imgB_fp);

        /* convert files to Pnm_ppm types */
        imgA = Pnm_ppmread(imgA_fp, methods);
        imgB = Pnm_ppmread(imgB_fp, methods);

        /* call calculate diff function */
        float diff = calculate_ppm_diff(methods, imgA, imgB);

        /* output calculated difference */
        fprintf(stdout, "%f\n", diff);

        /* free memory */
        Pnm_ppmfree(&imgA);
        Pnm_ppmfree(&imgB);

        return EXIT_SUCCESS;
}

float calculate_ppm_diff(A2Methods_T methods, Pnm_ppm imgA, Pnm_ppm imgB)
{
        int widthA = methods->width(imgA->pixels);
        int widthB = methods->width(imgB->pixels);
        int heightA = methods->height(imgA->pixels);
        int heightB = methods->height(imgB->pixels);
        int small_width = (widthA < widthB)?(widthA):(widthB);
        int small_height = (heightA < heightB)?(heightA):(heightB);

        if (abs(widthA - widthB) > 1 || abs(heightA - heightB) > 1) {
                fprintf(stderr, "image dimensions invalid\n");
                return 1;
        }

        float sum = 0;

        /* nested for-loop over each pixel */
        for (int row = 0; row < small_height; row++) {
            for (int col = 0; col < small_width; col++) {
                sum += sum_rgb_values(methods->at(imgA->pixels,col,row),
                                      methods->at(imgB->pixels,col,row));
            }
        }

        return sqrt(sum/(3*small_width*small_height));  
}

float sum_rgb_values(void *pixelA, void *pixelB)
{
        Pnm_rgb pxlA = (Pnm_rgb)pixelA;
        Pnm_rgb pxlB = (Pnm_rgb)pixelB;

        float diff_red = (float)pow(pxlA->red - pxlB->red,2);
        float diff_green = (float)pow(pxlA->green - pxlB->green,2);
        float diff_blue = (float)pow(pxlA->blue - pxlB->blue,2);
        
        return diff_red + diff_green + diff_blue;
}