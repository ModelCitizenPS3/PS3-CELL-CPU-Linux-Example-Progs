#include <stdio.h>
#include <massv.h>
#include <simdmath.h>
#include <spu_mfcio.h>

#define N 1000

typedef union {
    vector float vec[N];
    float scal[N * 4];
} floatType;

int main(int argc, char **argv)
{
    int i, n = N * 4;
    floatType testVec, result;
    unsigned int time, start, end;

    /* Initialize the test arrays */
    for (i = 0; i < N * 4; i++)
        testVec.scal[i] = (float)i;

    /* Test the SIMD Math function */
    spu_write_decrementer(0);
    for (i = 0; i < N; i++)
        result.vec[i] = logf4(testVec.vec[i]);
    time = -spu_read_decrementer();
    printf("SIMD: ln(2000) = %f\n", spu_extract(result.vec[500], 0));

    /* Test the MASSV function */
    start = spu_read_decrementer();
    vslog(result.scal, testVec.scal, &n);
    end = spu_read_decrementer();
    printf("MASSV: ln(2000) = %f\n", result.scal[2000]);

    /* Display the results */
    printf("SIMD Math: Time = %u\n", time);
    printf("MASSV: Time = %u\n", start - end);
    return 0;
}

