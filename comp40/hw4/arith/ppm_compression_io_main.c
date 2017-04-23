#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ppm_compression_io.h"

int main(int argc, char const *argv[])
{
        
        FILE *fp = fopen(argv[1], "r");

        Pnm_ppm img = read_header(fp);
        for (unsigned i = 0; i < 6; i++) {
           print_codeword(read_codeword(fp));     
        }

        // Pnm_ppm img = read_header(fp);
        // fprintf(stderr,"width: %u, height: %u, denom: %u\n",img->width,img->height,img->denominator);

        (void) img;
        (void) argv;
        (void) argc;
        
        return 0;
}
