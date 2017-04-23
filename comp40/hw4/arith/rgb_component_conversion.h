/* 
 * Assignment #4: Arith (2/25/15)
 * Ben Tanen, Julia Moyer
 * RGB to Component Conversion Module Interface
 *
 * Interface to convert from RGB to Component video (and back)
 */

#ifndef RGB_COMPONENT_CONVERSION_INCLUDED
#define RGB_COMPONENT_CONVERSION_INCLUDED

/* equations used to obtain component video from RGB (from assignment doc) */
float rgb_to_component_Y(float r, float g, float b);
float rgb_to_component_Pb(float r, float g, float b);
float rgb_to_component_Pr(float r, float g, float b);

/* equations used to obtain RGB from component video (from assignment doc) */
/* returns RGB values as floats, to later be scaled with image denominator */
float component_to_rgb_r(float Y, float Pb, float Pr);
float component_to_rgb_g(float Y, float Pb, float Pr);
float component_to_rgb_b(float Y, float Pb, float Pr);

#endif
