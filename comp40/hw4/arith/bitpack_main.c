#include <stdio.h>
#include <stdlib.h>

#include "bitpack.h"
#include <stdint.h>
#include "assert.h"
#include <time.h>

void check_laws_u(uint64_t word, unsigned w, unsigned lsb, uint64_t val,
                unsigned w2, unsigned lsb2);
void check_laws_s(uint64_t word, unsigned w, unsigned lsb, int64_t val,
                unsigned w2, unsigned lsb2);
void exhaustive_test(uint64_t num_trials);

int main()
{
        /* testing fits */
        /*
        int bound = 10;
        for (int i = -bound; i <= bound; i++) {
                printf("num: %i -> u: %i, s: %i\n",i,(int)Bitpack_fitsu(i,3),
                                                     (int)Bitpack_fitss(i,3));
                
        }
        */

        /* testing gets */
        // int word = 732;
        // int width = 6;
        // int lsb = 0;
        // printf("from: %i - get: %i\n",(int)word,(int)Bitpack_gets(word,width,lsb));

        // exhaustive_test(2000);

        return 0;
}

void check_laws_u(uint64_t word, unsigned w, unsigned lsb, uint64_t val,
                  unsigned w2, unsigned lsb2)
{
        TRY
            assert(Bitpack_getu(Bitpack_newu(word, w, lsb, val), w, lsb) == val);
            if (lsb2 >= w + lsb) assert(Bitpack_getu(Bitpack_newu(word, w, lsb, val), w2, lsb2) 
                                                                == Bitpack_getu(word, w2, lsb2));
            if (lsb2 >= w + lsb) assert(Bitpack_newu(Bitpack_newu(word,w,lsb,val),w2,lsb2,val) 
                                       == Bitpack_newu(Bitpack_newu(word,w2,lsb2,val),w,lsb,val));
        ELSE
            if (Bitpack_fitsu(val,w) && Bitpack_fitsu(val,w2)) fprintf(stderr, "You suck at unsigned @ %lu, %u, %u, %u, %u\n",word,w,lsb,w2,lsb2);
        END_TRY;
}

void check_laws_s(uint64_t word, unsigned w, unsigned lsb, int64_t val,
                  unsigned w2, unsigned lsb2)
{
        TRY
                assert(Bitpack_gets(Bitpack_news(word, w, lsb, val), w, lsb) == val);
                if (lsb2 >= w + lsb) {
                    assert(Bitpack_gets(Bitpack_news(word, w, lsb, val), w2, lsb2) 
                                        == Bitpack_gets(word, w2, lsb2));
                    assert(Bitpack_news(Bitpack_news(word,w,lsb,val),w2,lsb2,val) 
                                        == Bitpack_news(Bitpack_news(word,w2,lsb2,val),w,lsb,val));
                }
        ELSE
                if (Bitpack_fitss(val,w) && Bitpack_fitss(val,w2)) {
                    fprintf(stderr, "You suck at signed   @ %lu, %li, %u, %u, %u, %u\n",word,val,w,lsb,w2,lsb2);
                }
        END_TRY;

}

void exhaustive_test(uint64_t num_trials)
{
    FILE *randfp = fopen("/dev/urandom","rb");
    assert(randfp != NULL);
    srand(time(NULL));

    for (unsigned w = 0; w <= 64; w++) {
        for (unsigned lsb = 0; lsb + w <= 64; lsb++) {
            /* test with random numbers */
            for (unsigned trial = 0; trial < num_trials; trial++){
                
                // set random values
                uint64_t word;
                size_t rc = fread(&word, sizeof(word), 1, randfp);
                assert(rc == 1);

                // set random val, w2, lsb2
                uint64_t val  = rand();
                unsigned w2;
                unsigned lsb2;

                do {
                        w2   = rand() % 65;
                        lsb2 = rand() % 65;
                } while (w2 + lsb2 >= 64);

                check_laws_s(word, w, lsb, val, w2, lsb2);
                check_laws_u(word, w, lsb, val, w2, lsb2);
            }
        }
    }
}

