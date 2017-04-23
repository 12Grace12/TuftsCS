#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include "pnmrdr.h"
#include "except.h"
#include "assert.h"

#define DIMENSION 9

Pnmrdr_T convert_img_to_pnm(FILE *fp);
int read_sudoku(Pnmrdr_T pnm, UArray2_T arr);
int check_puzzle(UArray2_T puzzle);
int check_col(UArray2_T puzzle, int col);
int check_row(UArray2_T puzzle, int row);
int check_square(UArray2_T puzzle, int col, int row);

int main(int argc, char *argv[])
{
        /* declare FILE and Pnmrdr_T */
        FILE *img = NULL;
        Pnmrdr_T pnm_sudoku;
        UArray2_T arr_sudoku = UArray2_new(DIMENSION,DIMENSION,sizeof(int));
        int successful_read = 1;
        int successful_check = 1;
        
        /* pass filename from command line */
        if (argc == 2) {
                img = fopen(argv[1],"rb");

        /* pass file binary from stdin */
        } else if (argc == 1) {
                img = stdin;
        }

        /* checks that img is not NULL */
        /* would be NULL if multiple arguments passed or fopen failed */
        assert(img);

        /* convert image to pnm */
        pnm_sudoku = convert_img_to_pnm(img);

        /* read sudoku puzzle from pnm, store in UArray2 */
        /* returns 0 if read was unsuccessful for some reason */
        successful_read = read_sudoku(pnm_sudoku, arr_sudoku);

        /* check if puzzle is solved (if it was read correctly) */
        /* stores 0 if puzzle not solved, 1 if successfully solved */
        if (successful_read == 1) 
                successful_check = check_puzzle(arr_sudoku);

        /* free memory */
        Pnmrdr_free(&pnm_sudoku);
        UArray2_free(&arr_sudoku);
        fclose(img);

        /* exits based on successful (either 1 or 0) */
        if (successful_read == 0 || successful_check == 0) exit(1);
        exit(0); 
}

/*
 * attempts to convert file to Pnmrdr_T format
 * if successful, return pointer to instance
 * if not, return NULL pointer
 */
Pnmrdr_T convert_img_to_pnm(FILE *fp)
{
        Except_T Convert_Failure = { "Bad Conversion" }; 

        /* attempt to convert file to Pnmrdr_T type */
        TRY
                Pnmrdr_T pnm_img = Pnmrdr_new(fp);
                if (Pnmrdr_data(pnm_img).type != Pnmrdr_gray) {
                        /* throw error */
                        RAISE(Convert_Failure);
                }
                
                /* return successful conversion */
                return pnm_img;

        /* if badformat exception thrown */
        EXCEPT(Pnmrdr_Badformat)
                RAISE(Convert_Failure); 
        END_TRY;

        return NULL; 
}

/* reads pixel intensity from pnm and stores in a UArray2 */
/* returns 0 if reading was unsuccessful */
int read_sudoku(Pnmrdr_T pnm, UArray2_T arr)
{
        /* checks that the puzzle has the proper dimensions and denominator */
        if (Pnmrdr_data(pnm).width != DIMENSION ||
            Pnmrdr_data(pnm).height != DIMENSION ||
            Pnmrdr_data(pnm).denominator != DIMENSION) return 1;

        /* for each pixel of the pnm_sudoku puzzle */
        for (volatile int row = 0; row < DIMENSION; row++) {
                for (volatile int col = 0; col < DIMENSION; col++) {
                        TRY
                                /* make sure that intensity is in range */
                                int intensity = Pnmrdr_get(pnm);
                                if (intensity < 0 || intensity > DIMENSION) {
                                        return 0;
                                }

                                /* store each pixel intensity in UArray */
                                *((int *)UArray2_at(arr,col,row)) = intensity;
                        EXCEPT(Pnmrdr_Count)
                                return 0;
                        END_TRY;
                }
        }
        
        /* successfully read sudoku puzzle to UArray2 */
        return 1;
}

/* runs checks on the puzzle (columns, rows, squares) for completeness */
int check_puzzle(UArray2_T puzzle) 
{
        /* variable to check for success of tests */
        int successful;
        
        /* check each of the 9 columns for completeness */
        for (int col = 0; col < DIMENSION; col++) {
                successful = check_col(puzzle,col);
                if (successful == 0) return 0;
        }

        /* check each of the 9 rows for completeness */
        for (int row = 0; row < DIMENSION; row++) {
                successful = check_row(puzzle,row);
                if (successful == 0) return 0;
        }

        /* 
         * checks each of the 9 squares for completeness
         * nested for loop specifies the 2D index for the middle of the
         * nine squares (indices: (1,1),(1,4),(1,7),(4,1),(4,4),(4,7),etc.)
         */
        for (int col = 1; col < DIMENSION; col = col + 3) {
                for (int row = 1; row < DIMENSION; row = row + 3) {
                        successful = check_square(puzzle,col,row);
                        if (successful == 0) return 0;
                }
        }

        /* if all checks were successful, puzzle is solved */
        return 1;
}

/*
 * checks for completeness in a particular column
 * completeness means that the column contains all integers 1 - 9
 * with no duplicates
 */
int check_col(UArray2_T puzzle, int col)
{
        /* initialize an array to store if integer is present in col */
        /* 1 if is present, 0 if not */
        int num_present[DIMENSION];
        for (int i = 0; i < DIMENSION; i++) num_present[i] = 0;

        /* checks all elements of col, sets corresponding value in */
        /* num_present (set to 1 for true) */
        for (int row = 0; row < DIMENSION; row++) {
                int number = *((int *)UArray2_at(puzzle,col,row));
                num_present[number - 1] = 1; 
        }

        /* checks that all numbers are present in col */ 
        for (int i = 0; i < DIMENSION; i++) {
                if (num_present[i] == 0) return 0;
        }
        return 1;
}

/*
 * checks for completeness in a particular row
 * completeness means that the row contains all integers 1 - 9
 * with no duplicates
 */
int check_row(UArray2_T puzzle, int row)
{
        /* initialize an array to store if integer is present in row */
        /* 1 if is present, 0 if not */
        int num_present[DIMENSION];
        for (int i = 0; i < DIMENSION; i++) num_present[i] = 0;

        /* checks all elements of row, sets corresponding value in */
        /* num_present (set to 1 for true) */
        for (int col = 0; col < DIMENSION; col++) {
                int number = *((int *)UArray2_at(puzzle,col,row));
                num_present[number - 1] = 1;
        }

        /* checks that all numbers are present in row */
        for (int i = 0; i < DIMENSION; i++) {
                if (num_present[i] == 0) return 0;
        }
        
        return 1;
}

/*
 * checks for completeness in a particular sub-square
 * completeness means that the sub-square contains all integers 1 - 9
 * with no duplicates
 */
int check_square(UArray2_T puzzle, int col, int row)
{
        /* initialize an array to store if integer is present in square */
        /* 1 if is present, 0 if not */
        int num_present[DIMENSION];
        for (int i = 0; i < DIMENSION; i++) num_present[i] = 0;

        /* 
         * checks all elements of square, sets corresponding value in
         * num_present (set to 1 for true)
         * uses variables d_col (delta column) and d_row to access each
         * element surrounding center
         */
        for (int d_col = -1; d_col <= 1; d_col++) {
                for (int d_row = -1; d_row <= 1; d_row++) {
                        int number = *((int *)UArray2_at(puzzle,
                                                         col + d_col,
                                                         row + d_row));
                        num_present[number - 1] = 1;
                }
        }

        /* checks that all numbers are present in square */
        for (int i = 0; i < DIMENSION; i++) {
                if (num_present[i] == 0) return 0;
        }
        
        return 1;
}
