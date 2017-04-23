#include <stdio.h>
#include <stdlib.h>
#include "bit2.h"
#include "stack.h"
#include "pnmrdr.h"
#include "except.h"

Pnmrdr_T convert_img_to_pnm(FILE *fp);
Bit2_T read_pnm_to_bit2(Pnmrdr_T pnm);
void unblack_edges(Bit2_T arr);
void check_curr_pxl(Bit2_T arr, int col, int row, Stack_T stack);
void check_surrounding_pxls(Bit2_T arr, int col, int row, Stack_T stack);
void print_pbm(Bit2_T arr);
void print_array(int col, int row, Bit2_T arr, int value, void *cl); 

/* struct used to hold 2D index of pixels */
typedef struct {
        int col;
        int row;
} index2D;

int main(int argc, char *argv[])
{
        /* declare new FILE, Pnmrdr_T, and Bit2_T */
        /* FILE set to NULL in case user passed more than 2 arguments */
        FILE *img = NULL;
        Pnmrdr_T pnm;
        Bit2_T arr;

        /* pass filename from command line */
        if (argc == 2) {
                img = fopen(argv[1],"rb");

        /* pass file binary from stdin */
        } else if (argc == 1) {
                img = stdin;
        }

        /* checks that img is not NULL */
        /* would be NULL if multiple arguments passed or fopen failed */
        if (img == NULL) {
                fprintf(stderr,"error: bad input\n");
                exit(EXIT_FAILURE);
        }

        /* convert image to pnm */
        pnm = convert_img_to_pnm(img);

        /* read from pnm, store in Bit2 */
        arr = read_pnm_to_bit2(pnm);

        /* convert black edges to white */
        unblack_edges(arr); 
       
        /* print array using mapping */ 
        print_pbm(arr);
        
        /* free all variables */
        Bit2_free(&arr);
        fclose(img);
        Pnmrdr_free(&pnm);

        return EXIT_SUCCESS; 
}

/*
 * attempts to convert file to Pnmrdr_T format
 * if successful, returns instance
 * if not, returns NULL
 */
Pnmrdr_T convert_img_to_pnm(FILE *fp)
{
        /* allocate new Pnmrdr_T, set to NULL, in case of conversion failure */
        Pnmrdr_T pnm_img = NULL;
        Except_T Convert_Failure = { "Bad Conversion" }; 

        /* attempt to convert file to Pnmrdr_T type */
        TRY
                pnm_img = Pnmrdr_new(fp);
                if (Pnmrdr_data(pnm_img).type != Pnmrdr_bit) {
                        /* throw error */
                        RAISE(Convert_Failure);
                }

        /* if badformat exception thrown */
        EXCEPT(Pnmrdr_Badformat)
                RAISE(Convert_Failure); 
        END_TRY;

        /* return conversion (will return NULL if unsuccessful) */
        return pnm_img; 
}

/* reads all bit values from pnm to Bit2_T and returns */
Bit2_T read_pnm_to_bit2(Pnmrdr_T pnm)
{
        /* allocate new 2D bit array based on width / height */
        int width = Pnmrdr_data(pnm).width;
        int height = Pnmrdr_data(pnm).height;
        Bit2_T arr = Bit2_new(width, height);

        /* for each pixel of the pnm into bit2 */
        for (int row = 0; row < height; row++) {
                for (int col = 0; col < width; col++) {
                        /* store each pixel value in Bit2 */
                        Bit2_put(arr,col,row,Pnmrdr_get(pnm)); 
                }
        }

        /* return now populated 2D bit array */
        return arr;
}

/* checks for blackedges (is black and is on edge or touches pixel on edge) */
/* and converts all black edges to white pixels */
void unblack_edges(Bit2_T arr)
{
        /* declare necessary variables */
        /* stack to hold black edge positions */
        Stack_T bit_stack = Stack_new();
        int col;
        int row;

        /* loop through top edge (row = 0, col varies) */
        row = 0;
        for (col = 0; col < Bit2_width(arr); col++) {
                check_curr_pxl(arr,col,row,bit_stack);
        }
        
        /* loop through bottom edge (row = height, col varies) */
        row = Bit2_height(arr) - 1;
        for (col = 0; col < Bit2_width(arr); col++) {
                check_curr_pxl(arr,col,row,bit_stack);
        }
        
        /* loop through left edge (col = 0, row varies) */
        col = 0;
        for (row = 0; row < Bit2_height(arr); row++) {
                check_curr_pxl(arr,col,row,bit_stack);
        }

        /* loop through right edge (col = width, row varies) */
        col = Bit2_width(arr) - 1;
        for (row = 0; row < Bit2_height(arr); row++) {
                check_curr_pxl(arr,col,row,bit_stack);
        }

        /* free previously allocated stack */
        Stack_free(&bit_stack);
}

/* checks if the current pxl is a black edge, and checks neighboring pxls */
void check_curr_pxl(Bit2_T arr, int col, int row, Stack_T stack)
{
        /* if current pixel is black, check surrounding pxls then convert */
        if (Bit2_get(arr,col,row) == 1) {
                check_surrounding_pxls(arr,col,row,stack);
                Bit2_put(arr,col,row,0);
        }

        /* while stack of pxls to convert is non-empty */
        while (Stack_empty(stack) == 0) {
                /* pop of top pxl position */
                /* check surrouding pixels */
                /* convert color (black to white) */
                /* free position struct */
                index2D *curr_pxl = Stack_pop(stack);
                check_surrounding_pxls(arr,curr_pxl->col,curr_pxl->row,stack);
                Bit2_put(arr,curr_pxl->col,curr_pxl->row,0);
                free(curr_pxl);
        }
}

/* checks neighboring pxls to see if they are black */
void check_surrounding_pxls(Bit2_T arr, int col, int row, Stack_T stack)
{
        /* check right pixel for black */
        if (col+1 < Bit2_width(arr) && Bit2_get(arr,col+1,row) == 1) {
                /* allocate struct for index, store index, push onto stack */
                index2D *bit_index = malloc(sizeof(index2D));
                bit_index->col = col+1;
                bit_index->row = row;
                Stack_push(stack,bit_index);
        }

        /* check left pixel for black */
        if (col-1 > 0 && Bit2_get(arr,col-1,row) == 1) {
                /* allocate struct for index, store index, push onto stack */
                index2D *bit_index = malloc(sizeof(index2D));
                bit_index->col = col-1;
                bit_index->row = row;
                Stack_push(stack,bit_index);
        }

        /* check below pixel for black */
        if (row+1 < Bit2_height(arr) && Bit2_get(arr,col,row+1) == 1) {
                /* allocate struct for index, store index, push onto stack */
                index2D *bit_index = malloc(sizeof(index2D));
                bit_index->col = col;
                bit_index->row = row+1;
                Stack_push(stack,bit_index);
        }

        /* check above pixel for black */
        if (row-1 > 0 && Bit2_get(arr,col,row-1) == 1) {
                /* allocate struct for index, store index, push onto stack */
                index2D *bit_index = malloc(sizeof(index2D));
                bit_index->col = col;
                bit_index->row = row-1;
                Stack_push(stack,bit_index);
        } 
}

/* prints out the pbm in the correct format */
void print_pbm(Bit2_T arr)
{
        /* declare comment to print for pbm file */
        char *comment = "[comment goes here]";

        /* print pbm header (type (P1), width, height, comment) */
        printf("P1\n%i %i\n# %s\n",Bit2_width(arr),Bit2_height(arr),comment);

        /* print array using map_row_major and print_array() */
        Bit2_map_row_major(arr,print_array,stdout);
}

/* used by mapping function to print out each individual element */
void print_array(int col, int row, Bit2_T arr, int value, void *cl)
{
        /* print value (either 0 or 1) of bit */
        /* if current bit is last in row, print new-line */
        fprintf(cl,"%i",value);
        if (col == Bit2_width(arr)-1) fprintf(cl,"\n");

        (void) row;
}
