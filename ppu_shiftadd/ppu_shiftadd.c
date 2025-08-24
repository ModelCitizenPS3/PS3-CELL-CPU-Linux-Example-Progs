#include <stdio.h>
#include <altivec.h>

#define N 64

/* Loads the values from a[] into vec_a[],
 * loads values from b[] into vec_b[],
 * and computes c[i] = a[i + 1] + b[i + 2]; */
int main(int argc, char **argv)
{
    int i;
    unsigned int a[N] __attribute__((aligned(16)));
    unsigned int b[N] __attribute__((aligned(16)));
    unsigned int c[N] __attribute__((aligned(16)));
    vector unsigned int vec_a[4], vec_b[4], vec_c[4];
    vector unsigned char index_a, index_b;
    vector unsigned int tempA, tempB;

    /* Fill a[] with even values, b[] with odd values */
    for (i = 0; i < N; i++) {
        a[i] = 2 * i;
        b[i] = 2 * i + 1;
    }

    /* Create the index vectors needed for shifting */
    index_a = vec_lvsl(1 * sizeof(int), a);
    index_b = vec_lvsl(2 * sizeof(int), b);

    /* Load the first four elements of a and b into temp */
    tempA = vec_ld(0, a);
    tempB = vec_ld(0, b);

    /* Execute the vectorized loop */
    int vecSize = sizeof(vector unsigned int);
    for (i = 0; i < N / 4; i += 4) {

        /* Load five vectors from a */
        vec_a[0] = tempA;
        vec_a[1] = vec_ld((i + 1) * vecSize, a);
        vec_a[2] = vec_ld((i + 2) * vecSize, a);
        vec_a[3] = vec_ld((i + 3) * vecSize, a);
        tempA = vec_ld((i + 4) * vecSize, a);

        /* Shift vec_a vectors left */
        vec_a[0] = vec_perm(vec_a[0], vec_a[1], index_a);
        vec_a[1] = vec_perm(vec_a[1], vec_a[2], index_a);
        vec_a[2] = vec_perm(vec_a[2], vec_a[3], index_a);
        vec_a[3] = vec_perm(vec_a[3], tempA, index_a);

        /* Load five vectors from b */
        vec_b[0] = tempB;
        vec_b[1] = vec_ld((i + 1) * vecSize, b);
        vec_b[2] = vec_ld((i + 2) * vecSize, b);
        vec_b[3] = vec_ld((i + 3) * vecSize, b);
        tempB = vec_ld((i + 4) * vecSize, b);

        /* Shift vec_b vectors left */
        vec_b[0] = vec_perm(vec_b[0], vec_b[1], index_b);
        vec_b[1] = vec_perm(vec_b[1], vec_b[2], index_b);
        vec_b[2] = vec_perm(vec_b[2], vec_b[3], index_b);
        vec_b[3] = vec_perm(vec_b[3], tempB, index_b);

        /* Add vectors */
        vec_c[0] = vec_add(vec_a[0], vec_b[0]);
        vec_c[1] = vec_add(vec_a[1], vec_b[1]);
        vec_c[2] = vec_add(vec_a[2], vec_b[2]);
        vec_c[3] = vec_add(vec_a[3], vec_b[3]);

        /* Store sum vectors */
        vec_st(vec_c[0], (i + 0) * vecSize, c);
        vec_st(vec_c[1], (i + 1) * vecSize, c);
        vec_st(vec_c[2], (i + 2) * vecSize, c);
        vec_st(vec_c[3], (i + 3) * vecSize, c);
    }

    for (i = 0; i < N; i++)
        printf("%u ", c[i]);
    printf("\n");
    return 0;
}

