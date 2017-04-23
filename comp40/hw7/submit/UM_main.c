/*
 * UM_main.c
 * by Ben Tanen and Rebecca Larson
 *
 * The main program to run the UM
 * Uses the UM and memory segment ADTs to successfully
 * emulate the operations of a universal machine.
 * Specifics of the UM / memory segment implementations can be found
 * in the UM.c and seg.c files respectively.
 */

#include <stdio.h>
#include <stdlib.h>

#include "UM.h"

/* reads in the file specified by the user on the command line */
FILE *read_in_file(int argc, char *argv[])
{
        if (argc != 2) {
                fprintf(stderr, "Error: Incorrect Number of Arguments\n"); 
                return NULL;
        }

        FILE *fp = fopen(argv[1], "rb"); 
        
        if (fp == NULL) {
                fprintf(stderr, "Error: File Doesn't Exist\n");
                return NULL;
        }

        return fp;
}

int main(int argc, char *argv[])
{
        FILE *fp = read_in_file(argc, argv);
        if (fp == NULL) return EXIT_FAILURE;

        UM_new();
        UM_read_program(fp);
        UM_run_program();
        UM_free();
        fclose(fp);
}

