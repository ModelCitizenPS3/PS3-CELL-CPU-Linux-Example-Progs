#include <stdio.h>
#include <altivec.h>
#include <ppu_intrinsics.h>

#define N 8

typedef union {
    vector signed int vec;
    int scalars[4];
} intVecType;

int main(int argc, char **argv)
{
    int i;
    intVecType vec_a, vec_b, vec_sum;

    /* Initialize vec_a and vec_b */
    vec_a.vec = (vector signed int){0x08888888, 0x07777777, 0x06666666, 0x05555555};
    vec_b.vec = (vector signed int){0x04444444, 0x03333333, 0x02222222, 0x01111111};

    /* Add all elements of vec_a and vec_b */
    vec_sum.vec = vec_add(vec_a.vec, vec_b.vec);
    for (i = 0; i < 4; i++)
        printf("%08x ", vec_sum.scalars[i]);
    printf("\n");
    /* 0ccccccc 0aaaaaaa 08888888 06666666 */

    /* Add elements of vec_a to element 0 of vec_b */
    vec_sum.vec = vec_sums(vec_a.vec, vec_b.vec);
    for (i = 0; i < 4; i++)
        printf("%08x ", vec_sum.scalars[i]);
    printf("\n");
    /* 00000000 00000000 00000000 1ccccccb */

    vec_sum.vec = vec_sum2s(vec_a.vec, vec_b.vec);
    for (i = 0; i < 4; i++)
        printf("%08x ", vec_sum.scalars[i]);
    printf("\n");
    /* 00000000 13333332 00000000 0ccccccc */

    return 0;
}

