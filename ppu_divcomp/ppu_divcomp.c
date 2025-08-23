#include <stdio.h>
#include <stdlib.h>
#include <massv.h>
#include <ppu_intrinsics.h>
#include <simdmath.h>
#include <simdmath/divf4.h>
#include <simdmath/divf4_fast.h>

/* Number of vectors to be processed */
#define N 100

typedef union {
    vector float vec[N];
    float scalars[N * 4];
} floatType;

int main(int argc, char **argv)
{
    int i;
    unsigned long long start, end;
    float time;
    floatType a, b, c;

    /* Initialize vector/scalar values */
    for (i = 0; i < N * 4; i++) {
        a.scalars[i] = (float)rand() / RAND_MAX;
        b.scalars[i] = (float)rand() / RAND_MAX;
    }

    /* Test divf4 (inline) */
    start = __mftb();
    for (i = 0; i < N; i++)
        c.vec[i] = _divf4(a.vec[i], b.vec[i]);
    end = __mftb();
    time = (float)(end - start) / (N * 4);
    printf("Ticks per op for divf4 (inline): %f\n", time);

    /* Test divf4_fast (inline) */
    start = __mftb();
    for (i = 0; i < N; i++)
        c.vec[i] = _divf4_fast(a.vec[i], b.vec[i]);
    end = __mftb();
    time = (float)(end - start) / (N * 4);
    printf("Ticks per op for divf4_fast (inline): %f\n", time);

    /* Test divf4 */
    start = __mftb();
    for (i = 0; i < N; i++)
        c.vec[i] = divf4(a.vec[i], b.vec[i]);
    end = __mftb();
    time = (float)(end - start) / (N * 4);
    printf("Ticks per op for divf4: %f\n", time);

    /* Test divf4_fast */
    start = __mftb();
    for (i = 0; i < N; i++)
        c.vec[i] = divf4_fast(a.vec[i], b.vec[i]);
    end = __mftb();
    time = (float)(end - start) / (N * 4);
    printf("Ticks per op for divf4_fast: %f\n", time);

    /* Test the vsdiv function */
    int num_tests = N * 4;
    start = __mftb();
    vsdiv(c.scalars, a.scalars, b.scalars, &num_tests);
    end = __mftb();
    time = (float)(end - start) / (N * 4);
    printf("Ticks per op for vsdiv: %f\n", time);

    return 0;
}

