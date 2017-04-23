/* 
 * ppmtrans.c
 * by: Ben Tanen and McKenzie Welter
 * assignment: COMP-40 hw #3 (part c)
 *
 * This is the implementation for the .ppm image rotation program.
 * It performs a given transformation (rotate 0, 90, 180 or 270 degrees; flip
 * vertically or horizontally; or transpose) on a passed image and outputs the
 * transformed version of the image.
 *
 * Uses a pnm_ppm struct to store an image pixmap and the methods (from the
 * A2 methods suite) that can be performed on the pixmap. The pixmap is stored
 * as a 2D array.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "assert.h"
#include "a2methods.h"
#include "a2plain.h"
#include "a2blocked.h"
#include "pnm.h"

/* enum used to specify type of rotation */
typedef enum {rotate, flip_vert, flip_horiz, transp} trans_t; 

/* struct used as closure for mapping functions */
/* holds methods to be performed and Pnm_ppm that will hold transformed img */
typedef struct {
       A2Methods_T methods; 
       Pnm_ppm new_img;
} closure;

/* apply functions used to perform translations */
/* called by map() */
void rotate90(int i, int j, A2Methods_UArray2 array2, void *elem, void *cl);
void rotate180(int i, int j, A2Methods_UArray2 array2, void *elem, void *cl);
void rotate270(int i, int j, A2Methods_UArray2 array2, void *elem, void *cl);
void flip_v(int i, int j, A2Methods_UArray2 array2, void *elem, void *cl);
void flip_h(int i, int j, A2Methods_UArray2 array2, void *elem, void *cl);
void transpose(int i, int j, A2Methods_UArray2 array2, void *elem, void *cl);

/* function used when reading from command-line results in error */
static void usage(const char *progname)
{
        fprintf(stderr, "Usage: %s [-rotate <angle>] "
                "[-{row,col,block}-major] [filename]\n",
                progname);
        exit(1);
}

int main(int argc, char *argv[]) 
{
        /* initializes translation / rotation values */
        int i;
        int rotation = 0;
        trans_t translation;

        /* default to UArray2 methods */
        A2Methods_T methods = uarray2_methods_plain; 
        assert(methods); 

        /* default to best map */
        A2Methods_mapfun *map = methods->map_default; 
        assert(map);

/* following code was provided by the staff of COMP-40 */
/* it reads commands from command-line and interprets them accordingly */
#define SET_METHODS(METHODS, MAP, WHAT) do {                            \
                methods = (METHODS);                                    \
                assert(methods != NULL);                                \
                map = methods->MAP;                                     \
                if (map == NULL) {                                      \
                        fprintf(stderr, "%s does not support "          \
                                        WHAT "mapping\n",               \
                                argv[0]);                               \
                        exit(1);                                        \
                }                                                       \
        } while (0)

        for (i = 1; i < argc; i++) {
                if (!strcmp(argv[i], "-row-major")) {
                        SET_METHODS(uarray2_methods_plain, map_row_major,
                                    "row-major");
                } else if (!strcmp(argv[i], "-col-major")) {
                        SET_METHODS(uarray2_methods_plain, map_col_major,
                                    "column-major");
                } else if (!strcmp(argv[i], "-block-major")) {
                        SET_METHODS(uarray2_methods_blocked, map_block_major,
                                    "block-major");
                } else if (!strcmp(argv[i], "-rotate")) {
                        if (!(i + 1 < argc)) {      /* no rotate value */
                                usage(argv[0]);
                        }
                        char *endptr;
                        rotation = strtol(argv[++i], &endptr, 10);
                        if (!(rotation == 0 || rotation == 90
                              || rotation == 180 || rotation == 270)) {
                                fprintf(stderr, "Rotation must be "
                                        "0, 90 180 or 270\n");
                                usage(argv[0]);
                        }
                        if (!(*endptr == '\0')) {    /* Not a number */
                                usage(argv[0]);
                        }
                        translation = rotate;

                /* following two branches of if-tree written by students */
                /* checks for transpose and flip commands */
                } else if (!strcmp(argv[i], "-transpose")){
                        translation = transp;
                } else if (!strcmp(argv[i], "-flip")){
                        if (!(i + 1 < argc)) {      /* no flip direction */
                                usage(argv[0]);
                        }
                        if (!(strcmp(argv[++i],"horizontal"))) 
                                translation = flip_horiz;
                        else if (!(strcmp(argv[i],"vertical"))) 
                                translation = flip_vert;
                        else {
                                fprintf(stderr, "Flip must be "
                                        "vertical or horizontal\n");
                                usage(argv[0]);
                        }
                } else if (*argv[i] == '-') {
                        fprintf(stderr, "%s: unknown option '%s'\n", argv[0],
                                argv[i]);
                } else if (argc - i > 1) {
                        fprintf(stderr, "Too many arguments\n");
                        usage(argv[0]);
                } else {
                        break;
                }
        }



        /* closure including methods suite */
        closure cl;
        cl.methods = methods;
      
        /* declare new FILE, Pnmrdr_T, and Bit2_T */
        /* FILE set to NULL in case user passed more than 2 arguments */
        FILE *img_fp = NULL;
        Pnm_ppm img;

        /* pass file binary from stdin */
        if (argv[argc-1][0] == '-') {
                img_fp = stdin;

        /* pass filename from command line */
        } else {
                img_fp = fopen(argv[argc-1],"rb");
        }

        /* checks that img is not NULL */
        /* would be NULL if fopen failed */
        assert(img_fp);

        /* make new Pnm_ppm from image coming from input file */
        img = Pnm_ppmread(img_fp, methods);

        /* create a new Pnm_ppm struct to store transformed image */
        /* initialize with known denominator and methods */
        /* store in closure for use in mapping functions */
        Pnm_ppm new_img = malloc(sizeof(*new_img));
        new_img->denominator = img->denominator;
        new_img->methods = methods;
        cl.new_img = new_img;

        /* check which type of translation is being done */
        /* if rotate 90, rotate 270, or transpose */
        if((translation == rotate && (rotation == 90 || rotation == 270)) ||
           (translation == transp)) { 
                /* if translation is rotate 90 / 270 or transpose, */ 
                /* need image with inverse dimensions */ 
                cl.new_img->width = img->height;
                cl.new_img->height = img->width;
                cl.new_img->pixels = methods->new(img->height, img->width,
                                               methods->size(img->pixels));

                /* check which type of translation, and map using that fxn */
                if(translation == transp) map(img->pixels,transpose,&cl);
                else if(rotation == 90) map(img->pixels,rotate90,&cl);
                else if(rotation == 270) map(img->pixels,rotate270,&cl);

        /* if rotate 180, flip vertical, or flip horizontal */
        } else if((translation == rotate && rotation == 180) ||
                 translation == flip_vert || translation == flip_horiz){ 
                /* if translation is rotate 180 or flip, */ 
                /* need image with same dimensions as original */ 
                cl.new_img->width = img->width;
                cl.new_img->height = img->height;
                cl.new_img->pixels = methods->new(img->width, img->height,
                                               methods->size(img->pixels));

                /* check which type of translation, and map using that fxn */
                if(translation == rotate) map(img->pixels,rotate180,&cl);
                else if(translation == flip_vert) map(img->pixels,flip_v,&cl);
                else if(translation == flip_horiz) map(img->pixels,flip_h,&cl);

        /* if rotate 0 */
        } else if(translation == rotate && rotation == 0){
                /* do nothing, store original image as new image */
                cl.new_img = img;
        }

        /* write now transformed image back to stdout */
        Pnm_ppmwrite(stdout, cl.new_img);

        /* free used memory */
        Pnm_ppmfree(&new_img);
        Pnm_ppmfree(&img);
        fclose(img_fp);
        return EXIT_SUCCESS;
}

/* function used by map() to rotate image 90 degrees */
/* stores new image in Pnm_ppm new_img held within closure */
void rotate90(int col, int row, A2Methods_UArray2 array2, void *elem, void *cl)
{
        /* get methods and new_img from passed closure */
        A2Methods_T methods = (*(closure *)cl).methods;
        Pnm_ppm new_img = (*(closure *)cl).new_img;

        /* calculate new col and new row values for translation */
        int new_col = methods->height(array2) - row - 1;
        int new_row = col;

        /* store rgb struct from original position in img */
        /* new position in new_img */
        *((Pnm_rgb)methods->at(new_img->pixels,new_col,new_row)) = 
                                                             *((Pnm_rgb)elem);
}

/* function used by map() to rotate image 270 degrees */
/* stores new image in Pnm_ppm new_img held within closure */
void rotate270(int col, int row, A2Methods_UArray2 array2, void *elem, void *cl)
{
        /* get methods and new_img from passed closure */
        A2Methods_T methods = (*(closure *)cl).methods;
        Pnm_ppm new_img = (*(closure *)cl).new_img;

        /* calculate new col and new row values for translation */
        int new_col = row;
        int new_row = methods->width(array2) - col - 1;

        /* store rgb struct from original position in img */
        /* new position in new_img */
        *((Pnm_rgb)methods->at(new_img->pixels,new_col,new_row)) = 
                                                             *((Pnm_rgb)elem);
}

/* function used by map() to rotate image 180 degrees */
/* stores new image in Pnm_ppm new_img held within closure */
void rotate180(int col, int row, A2Methods_UArray2 array2, void *elem, void *cl)
{        
        /* get methods and new_img from passed closure */
        A2Methods_T methods = (*(closure *)cl).methods;
        Pnm_ppm new_img = (*(closure *)cl).new_img;

        /* calculate new col and new row values for translation */
        int new_col = (methods->width(array2) - 1) - col;
        int new_row = (methods->height(array2) - 1) - row;

        /* store rgb struct from original position in img */
        /* new position in new_img */
        *((Pnm_rgb)methods->at(new_img->pixels,new_col,new_row)) = 
                                                             *((Pnm_rgb)elem);
}

/* function used by map() to flip image vertically */
/* stores new image in Pnm_ppm new_img held within closure */
void flip_v(int col, int row, A2Methods_UArray2 array2, void *elem, void *cl) 
{
        /* get methods and new_img from passed closure */
        A2Methods_T methods = (*(closure *)cl).methods;
        Pnm_ppm new_img = (*(closure *)cl).new_img;

        /* calculate new row value for translation */
        int new_row = (methods->height(array2) - 1) - row;

        /* store rgb struct from original position in img */
        /* new position in new_img */
        *((Pnm_rgb)methods->at(new_img->pixels,col,new_row)) = *((Pnm_rgb)elem);
}

/* function used by map() to flip image horizontally */
/* stores new image in Pnm_ppm new_img held within closure */
void flip_h(int col, int row, A2Methods_UArray2 array2, void *elem, void *cl) 
{
        /* get methods and new_img from passed closure */
        A2Methods_T methods = (*(closure *)cl).methods;
        Pnm_ppm new_img = (*(closure *)cl).new_img;

        /* calculate new col value for translation */
        int new_col = (methods->width(array2) - 1) - col;

        /* store rgb struct from original position in img */
        /* new position in new_img */
        *((Pnm_rgb)methods->at(new_img->pixels,new_col,row)) = *((Pnm_rgb)elem);
}

/* function used by map() to transpose image */
/* stores new image in Pnm_ppm new_img held within closure */
void transpose(int col, int row, A2Methods_UArray2 array2, void *elem, void *cl)
{
        /* get methods and new_img from passed closure */
        A2Methods_T methods = (*(closure *)cl).methods;
        Pnm_ppm new_img = (*(closure *)cl).new_img;

        /* calculate new col and new row values for translation */
        int new_col = row;
        int new_row = col;

        /* store rgb struct from original position in img */
        /* new position in new_img */
        *((Pnm_rgb)methods->at(new_img->pixels,new_col,new_row)) = 
                                                             *((Pnm_rgb)elem);
        (void)array2;
}
