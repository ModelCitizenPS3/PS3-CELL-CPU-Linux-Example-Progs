#include <stdio.h>
#include <altivec.h>

typedef union {
    vector unsigned int vec;
    unsigned int scalars[4];
} intType;

int main(int argc, char **argv)
{
    vector unsigned int vec_a, vec_b;
    vector unsigned char indexVec;
    intType result;

    /* Initialize the input vectors */
    vec_a = (vector unsigned int){0, 1, 2, 3};
    vec_b = (vector unsigned int){4, 5, 6, 7};

    /* Initialize the index vector */
    indexVec = (vector unsigned char){8, 9, 10, 11, 16, 17, 18, 19, 0, 1, 2, 3, 24, 25, 26, 27};

    /* Place the selected bytes in the result */
    result.vec = vec_perm(vec_a, vec_b, indexVec);

    printf("%u %u %u %u\n", result.scalars[0], result.scalars[1], result.scalars[2], result.scalars[3]);
    return 0;
}

