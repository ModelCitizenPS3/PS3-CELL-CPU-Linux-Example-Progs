#include <stdio.h>
#include <spu_intrinsics.h>

typedef struct {
    int count;      /* # of ints in the array */
    int num[16];    /* int array that forms the number */
} BIGNUM;

int main(int argc, char **argv)
{
    int i;
    BIGNUM test __attribute__((aligned(16)));

    /* Initialize the BIGNUM struct */
    test.count = 16;
    for (i = 0; i < 16; i++)
        test.num[i] = i;

    /* Create the vector array */
    vector signed int *intvec = (vector signed int *)&test;

    /* Shift each vector left by four bytes */
    vector unsigned char indexVec = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    for (i = 0; i < 4; i++)
        intvec[i] = spu_shuffle(intvec[i], intvec[i + 1], indexVec);

    /* Display the shifted vectors */
    for (i = 0; i < 4; i++)
        printf("%d %d %d %d\n", spu_extract(intvec[i], 0), spu_extract(intvec[i], 1), spu_extract(intvec[i], 2), spu_extract(intvec[i], 3));

    return 0;
}

