/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * Discrete Cosine Module Interface
 *
 * Interface of given equations (from assignment document) to
 * calculate discrete cosine (and inverse discrete cosine) values.
 */

#ifndef DISCRETE_COSINE_INCLUDED
#define DISCRETE_COSINE_INCLUDED

#include <stdint.h>

/*
 * equations used to obtain cosine coefficients of discrete cosine come from
 * provided assignment document.
 */
uint64_t discr_cos_a(float Y_1, float Y_2, float Y_3, float Y_4);
int64_t  discr_cos_b(float Y_1, float Y_2, float Y_3, float Y_4);
int64_t  discr_cos_c(float Y_1, float Y_2, float Y_3, float Y_4);
int64_t  discr_cos_d(float Y_1, float Y_2, float Y_3, float Y_4);

/*
 * equations used to obtain original Y-values from inverse discrete cosine come
 * from provided assignment document.
 */
float inv_discr_cos_Y1(uint64_t a, int64_t b, int64_t c, int64_t d);
float inv_discr_cos_Y2(uint64_t a, int64_t b, int64_t c, int64_t d);
float inv_discr_cos_Y3(uint64_t a, int64_t b, int64_t c, int64_t d);
float inv_discr_cos_Y4(uint64_t a, int64_t b, int64_t c, int64_t d);

#endif
