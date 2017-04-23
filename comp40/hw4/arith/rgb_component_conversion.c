/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * RGB to Component Conversion Module Implemenation
 *
 * Implementations of given equations (from assignment document) to
 * convert from RGB to Component video (and back)
 */

#include "rgb_component_conversion.h"

/* returns value closest to value allowed within bounds */
static inline float val_within_bounds(float val, float hi_bound, float lo_bound)
{
        if (val >= hi_bound) return hi_bound;
        else if (val <= lo_bound) return lo_bound;
        else return val;  
}

/* equations used to obtain component video from RGB (from assignment doc) */
float rgb_to_component_Y(float r, float g, float b)
{
        return 0.299 * r + 0.587 * g + 0.114 * b;
}

float rgb_to_component_Pb(float r, float g, float b)
{
        return -0.168736 * r - 0.331264 * g + 0.5 * b;
}

float rgb_to_component_Pr(float r, float g, float b)
{
        return 0.5 * r - 0.418688 * g - 0.081312 * b;
}

/* equations used to obtain RGB from component video (from assignment doc) */
/* returns RGB values as floats, to later be scaled with image denominator */
/* makes sure values being returned are within valid range (0-1) */
float component_to_rgb_r(float Y, float Pb, float Pr)
{
        float r = 1.0 * Y + 0.0 * Pb + 1.402 * Pr;
        return val_within_bounds(r, 1.0, 0.0);
}

float component_to_rgb_g(float Y, float Pb, float Pr)
{
        float g = 1.0 * Y - 0.344136 * Pb - 0.714136 * Pr;
        return val_within_bounds(g, 1.0, 0.0);     
}

float component_to_rgb_b(float Y, float Pb, float Pr)
{
        float b =  1.0 * Y + 1.772* Pb + 0.0 * Pr;
        return val_within_bounds(b, 1.0, 0.0);   
}