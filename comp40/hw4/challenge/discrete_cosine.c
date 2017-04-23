/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * Discrete Cosine Module Implemenation
 *
 * Implementations of given equations (from assignment document) to
 * calculate discrete cosine (and inverse discrete cosine) values. Functions
 * ensure that return values are within proper bounds for value type.
 */

#include "discrete_cosine.h"
#include <math.h>

/* 
 * scaling factors used to convert float numbers to scaled integers
 * SCALING_FACTOR_A provided for unsigned 6-bit int
 * SCALING_FACTOR_BCD calculated for signed 6-bit int in range of -31...31
 * calculated using 31.5 / .3 > SCALING_FACTOR_BCD 
 */
const float SCALING_FACTOR_A = 63.0;
const float SCALING_FACTOR_BCD = 104.5;

/* returns value closest to value allowed within bounds */
static inline int64_t val_within_bounds(int64_t val, int hi_bound, int lo_bound)
{
        if (val >= hi_bound) return hi_bound;
        else if (val <= lo_bound) return lo_bound;
        else return val;  
}

/*
 * equations used to obtain cosine coefficients of discrete cosine come from
 * provided assignment document.
 * original calculation gives float, but using scaling factors and rounding,
 * below four functions return scaled integers
 */
uint64_t discr_cos_a(float Y_1, float Y_2, float Y_3, float Y_4)
{
        uint64_t a = round(((Y_4 + Y_3 + Y_2 + Y_1) / 4.0) * SCALING_FACTOR_A);
        return a;
}

int64_t  discr_cos_b(float Y_1, float Y_2, float Y_3, float Y_4)
{
        int64_t b = round(((Y_4 + Y_3 - Y_2 - Y_1) / 4.0) * SCALING_FACTOR_BCD);
        return val_within_bounds(b, 31, -31);
}

int64_t  discr_cos_c(float Y_1, float Y_2, float Y_3, float Y_4)
{
        int64_t c = round(((Y_4 - Y_3 + Y_2 - Y_1) / 4.0) * SCALING_FACTOR_BCD);
        return val_within_bounds(c, 31, -31);
}

int64_t  discr_cos_d(float Y_1, float Y_2, float Y_3, float Y_4)
{
        int64_t d = round(((Y_4 - Y_3 - Y_2 + Y_1) / 4.0) * SCALING_FACTOR_BCD);
        return val_within_bounds(d, 31, -31);
}


/*
 * equations used to obtain original Y-values from inverse discrete cosine come
 * from provided assignment document.
 * using scaled integers that are provided, de-scale integers using scaling
 * factors and cast to floats.
 */
float inv_discr_cos_Y1(uint64_t a, int64_t b, int64_t c, int64_t d)
{
        float fl_a = a / SCALING_FACTOR_A;
        float fl_b = b / SCALING_FACTOR_BCD;
        float fl_c = c / SCALING_FACTOR_BCD;
        float fl_d = d / SCALING_FACTOR_BCD;

        return fl_a - fl_b - fl_c + fl_d;
}

float inv_discr_cos_Y2(uint64_t a, int64_t b, int64_t c, int64_t d)
{
        float fl_a = a / SCALING_FACTOR_A;
        float fl_b = b / SCALING_FACTOR_BCD;
        float fl_c = c / SCALING_FACTOR_BCD;
        float fl_d = d / SCALING_FACTOR_BCD;

        return fl_a - fl_b + fl_c - fl_d;
}

float inv_discr_cos_Y3(uint64_t a, int64_t b, int64_t c, int64_t d)
{
        float fl_a = a / SCALING_FACTOR_A;
        float fl_b = b / SCALING_FACTOR_BCD;
        float fl_c = c / SCALING_FACTOR_BCD;
        float fl_d = d / SCALING_FACTOR_BCD;

        return fl_a + fl_b - fl_c - fl_d;
}

float inv_discr_cos_Y4(uint64_t a, int64_t b, int64_t c, int64_t d)
{
        float fl_a = a / SCALING_FACTOR_A;
        float fl_b = b / SCALING_FACTOR_BCD;
        float fl_c = c / SCALING_FACTOR_BCD;
        float fl_d = d / SCALING_FACTOR_BCD;

        return fl_a + fl_b + fl_c + fl_d;
}