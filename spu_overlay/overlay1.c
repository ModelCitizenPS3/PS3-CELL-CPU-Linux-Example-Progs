#include <stdio.h>
#include <spu_intrinsics.h>

vector unsigned int reverse_vector(vector unsigned int test)
{
    int i;
    vector unsigned char indexVec = {12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3};

    /* Rearrange the vector */
    test = spu_shuffle(test, test, indexVec);

    /* Display the results */
    printf("reverse vector: ");
    for (i = 0; i < 4; i++)
        printf("%u ", spu_extract(test, i));
    printf("\n");
    return test;
}

