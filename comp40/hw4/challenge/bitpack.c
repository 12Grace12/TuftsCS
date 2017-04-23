/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * Bitpack Module Implementation
 *
 * Implementation of functions used for bitpacking signed & unsigned integers.
 * Functions below can be used to check for fitting, retrieve information from
 * 'words', and make new words. Calculations done by using bitwise operations.
 */

#include "bitpack.h"
#include <stdio.h>
#include "except.h"
#include "assert.h"

Except_T Bitpack_Overflow = { "Overflow packing bits" };

const uint64_t one_64bit  = 1;
const uint64_t zero_64bit = 0;
const unsigned max_size   = 64;

/* checks if an unsigned value can fit into width-number of bits */
bool Bitpack_fitsu(uint64_t n, unsigned width)
{
        /* make sure width is with valid bounds */
        assert(width <= max_size);
        if (width == 0) return false;
        
        /* shifting n by width should clear all acceptable values making n=0 */
        return (n >> width) == 0;
}

/* checks if an signed value can fit into width-number of bits */
bool Bitpack_fitss(int64_t n, unsigned width)
{
        /* make sure width is with valid bounds */
        assert(width <= max_size);
        if (width == 0) return false;
 
        /* upper bound will be 2^(width - 1) since we have width - 1 bits */   
        int64_t upper_bound =  (one_64bit << (width - 1));
        
        /* lower bound will be two's complement of upper bound, minus 1 */
        int64_t lower_bound = ~(one_64bit << (width - 1));

        /* make sure n is within bounds */
        return (upper_bound > n) && (n > lower_bound); 
}

/* gets a unsigned value from a word with given width and starting at lsb */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb)
{
        /* make sure passed variables are within bounds */
        assert(lsb < max_size && width + lsb <= max_size);

        /* if width is 64, just return original untrimmed word */
        if (width == max_size) return word;
        else if (width == 0) return 0;

        /* make mask of width 1's, then move it over (shift-left) by lsb */
        int64_t mask = ((one_64bit << width) - 1) << lsb;

        /* word 'and'  mask returns just needed portion */
        /* then right-shift by lsb so return just that portion */
        return (word & mask) >> lsb;
}

/* gets a signed value from a word with given width and starting at lsb */
int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb)
{
        /* make sure passed variables are within bounds */
        assert(lsb < max_size && width + lsb <= max_size);

        /* if width is 64, just return original untrimmed word */
        if (width == max_size) return word;
        else if (width == 0) return 0;

        /* make mask of width 1's, then move it over (shift-left) by lsb */
        uint64_t mask = ((one_64bit << width) - 1) << lsb;

        /* if value to be extracted is negative (with leading 1) */
        /* return value with string of preceeding 1's to return negative val */
        if (Bitpack_getu(word, 1, lsb + width - 1) == 1) {
                return (~(zero_64bit) << width) | ((word & mask) >> lsb);
        }

        /* word 'and' mask returns just needed portion */
        /* then right-shift by lsb so return just that portion */
        /* (same procedure as Bitpack_getu) */
        return (word & mask) >> lsb;

}

/* return a new word with the bitfield specified by width / lsb updated to 
 * contain an unsigned value */
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
                      uint64_t value)
{
        /* check that new value will fit in word & width (using lsb, width) */
        assert(lsb < max_size && lsb + width <= max_size);
        if (!Bitpack_fitsu(value, width)) RAISE(Bitpack_Overflow);

        /* get portion from original in space to be updated */
        uint64_t old_value = Bitpack_getu(word, width, lsb);

        /* shift portion to lsb, use 'xor' to nullify space for new value */
        word = word ^ (old_value << lsb);

        /* shift value to lsb, use 'or' to store new value in cleared space */
        /* return updated word */ 
        return word | (value << lsb);
}

/* return a new word with the bitfield specified by width / lsb updated to 
 * contain an signed value */
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, 
                       int64_t value)
{
        /* check that new value will fit in word & width (using lsb, width) */
        assert(lsb < max_size && lsb + width <= max_size); 
        if (!Bitpack_fitss(value, width)) RAISE(Bitpack_Overflow);

        /* get portion from original in space to be updated */
        uint64_t old_value = Bitpack_getu(word, width, lsb);

        /* shift portion to lsb, use 'xor' to nullify space for new value */
        word = word ^ (old_value << lsb);

        /* shift value to lsb, use 'or' to store new value in cleared space */
        /* return updated word */
        return word | (Bitpack_getu(value, width, 0) << lsb);
}