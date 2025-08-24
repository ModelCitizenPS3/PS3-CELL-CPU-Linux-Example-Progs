#include <stdio.h>
#include <altivec.h>
#include <simdmath.h>

typedef union {
    vector float vec;
    float scalars[4];
} floatVecType;

int main(int argc, char **argv)
{
    floatVecType input, result;

    /* Initialize the input vector */
    input.vec = (vector float){ -2.5, -1.5, 1.5, 2.5 };
    printf("Input:        %.1f, %.1f, %.1f, %.1f\n", input.scalars[0], input.scalars[1], input.scalars[2], input.scalars[3]);

    /* vec_ceil */
    result.vec = vec_ceil(input.vec);
    printf("vec_ceil:     %.1f, %.1f, %.1f, %.1f\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);

    /* vec_floor */
    result.vec = vec_floor(input.vec);
    printf("vec_floor:    %.1f, %.1f, %.1f, %.1f\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);

    /* vec_round */
    result.vec = vec_round(input.vec);
    printf("vec_round:    %.1f, %.1f, %.1f, %.1f\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);

    /* roundf4 */
    result.vec = roundf4(input.vec);
    printf("roundf4:      %.1f, %.1f, %.1f, %.1f\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);

    /* nearbyintf4 */
    result.vec = nearbyintf4(input.vec);
    printf("nearbyintf4:  %.1f, %.1f, %.1f, %.1f\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);

    /* vec_trunc */
    result.vec = vec_trunc(input.vec);
    printf("vec_trunc:    %.1f, %.1f, %.1f, %.1f\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);

    return 0;
}

