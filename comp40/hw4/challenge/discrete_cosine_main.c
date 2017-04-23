#include <stdio.h>
#include <stdlib.h>

#include "discrete_cosine.h"

int main()
{
        float Y_1 = 1.0;
        float Y_2 = 1.0;
        float Y_3 = 0.0;
        float Y_4 = 0.0;
        printf("- - - Original Values - - -\n");
        printf("Y_1: %2.5f\n",Y_1);
        printf("Y_2: %2.5f\n",Y_2);
        printf("Y_3: %2.5f\n",Y_3);
        printf("Y_4: %2.5f\n",Y_4);

        uint64_t a = discr_cos_a(Y_1, Y_2, Y_3, Y_4);
        int64_t b = discr_cos_b(Y_1, Y_2, Y_3, Y_4);
        int64_t c = discr_cos_c(Y_1, Y_2, Y_3, Y_4);
        int64_t d = discr_cos_d(Y_1, Y_2, Y_3, Y_4);
        Y_1 = inv_discr_cos_Y1(a, b, c, d);
        Y_2 = inv_discr_cos_Y2(a, b, c, d);
        Y_3 = inv_discr_cos_Y3(a, b, c, d);
        Y_4 = inv_discr_cos_Y4(a, b, c, d);

        printf("\n- - - Discrete Cosine Values - - -\n");
        printf("a: %i\n",(int)a);
        printf("b: %i\n",(int)b);
        printf("c: %i\n",(int)c);
        printf("d: %i\n",(int)d);

        printf("\n- - - Inverse Discrete Cosine Values - - -\n");
        printf("Y_1: %2.5f\n",Y_1);
        printf("Y_2: %2.5f\n",Y_2);
        printf("Y_3: %2.5f\n",Y_3);
        printf("Y_4: %2.5f\n",Y_4);

        return 0;
}
