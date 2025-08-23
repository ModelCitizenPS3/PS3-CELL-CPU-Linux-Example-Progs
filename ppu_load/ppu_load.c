#include <stdio.h>
#include <altivec.h>
#include <ppu_intrinsics.h>

#define N 8

typedef union {
    vector unsigned int vec;
    unsigned int scalars[4];
} intVecType;

int main(int argc, char **argv)
{
    int i;
    unsigned int int_array[N] __attribute__((aligned(16)));
    intVecType vec_a, vec_b, vec_c;

    /* Initialize the array */
    for (i = 0; i < N; i++)
        int_array[i] = i;

    /* Load the first four ints into vec_a */
    vec_a.vec = vec_ld(0, int_array);
    for (i = 0; i < 4; i++)
        printf("%u ", vec_a.scalars[i]);
    printf("\n");

    /* Load the next four ints into vec_b */
    vec_b.vec = vec_lde(2, int_array + 4);
    for (i = 0; i < 4; i++)
        printf("%u ", vec_b.scalars[i]);
    printf("\n");

    /* Load 16 - 7 = 9 bytes into vec_c, left first */
    vec_c.vec = vec_lvlx(7, int_array);
    for (i = 0; i < 4; i++)
        printf("%08x ", vec_c.scalars[i]);
    printf("\n");
    /* 01000000 02000000 03000000 00000000 */

    return 0;
}

