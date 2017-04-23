/* 
 * Assignment #4: Arith
 * Ben Tanen, Julia Moyer
 * RGB Component Conversion Test File
 */

#include <stdio.h>
#include <stdlib.h>
#include "rgb_component_conversion.h"

int main()
{
        /* testing from rgb to component */
        int r = 5;
        int g = 3;
        int b = 4;
        float Y = rgb_to_component_Y(r, g, b);
        float Pr = rgb_to_component_Pr(r, g, b); 
        float Pb = rgb_to_component_Pb(r, g, b); 
/*
        printf("--- RGB to Component, back to RGB Test ---\n");
        printf("Red: %i - %i\n",r,component_to_rgb_r(Y, Pb, Pr));
        printf("Green: %i - %i\n",g,component_to_rgb_g(Y, Pb, Pr));
        printf("Blue: %i - %i\n\n",b,component_to_rgb_b(Y, Pb, Pr));
*/
        /* testing from rgb to component */
        Y = 3.15;
        Pr = 4.7; 
        Pb = 8.5;
        r = component_to_rgb_r(Y, Pb, Pr);
        g = component_to_rgb_g(Y, Pb, Pr);
        b = component_to_rgb_b(Y, Pb, Pr);
  /*       
        printf("--- Component to RGB, back to Component Test ---\n");
        printf("Y: %2.5f - %2.5f\n",Y,rgb_to_component_Y(r, g, b));
        printf("Pb: %2.5f - %2.5f\n",Pb,rgb_to_component_Pb(r, g, b));
        printf("Pr: %2.5f - %2.5f\n",Pr,rgb_to_component_Pr(r, g, b));
    */
        return 0;
}