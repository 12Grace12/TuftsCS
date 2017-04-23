/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * Bitpack Module Interface
 *
 * Interface of functions used for bitpacking signed and unsigned integers
 * Functions below can be used to check for fitting, retrieve information from
 * 'words', and make new 'words'
 */

#ifndef BITPACK_INCLUDED
#define BITPACK_INCLUDED

#include <stdbool.h>
#include <stdint.h>

/* checks if an value can fit into width-number of bits */
bool Bitpack_fitsu(uint64_t n, unsigned width);
bool Bitpack_fitss( int64_t n, unsigned width);

/* gets a value from a word with given width and starting at lsb */
uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb);
 int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb);

/* return a new word with the bitfield specified updated to contain value */
uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, 
                      uint64_t value);
uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb, 
                       int64_t value);

#endif