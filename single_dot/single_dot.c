#include <stdio.h>

#define N 1000

int vec1[N], vec2[N], sum;

/* Compute the dot product */
void dprod()
{
    int i;
    sum = 0;
    for (i = 0; i < N; i++)
        sum += vec1[i] * vec2[i];
}

int main(int argc, char **argv)
{
    int i;

    /* Initialize arrays */
    for (i = 0; i < N; i++) {
        vec1[i] = i;
        vec2[i] = N - i;
    }
    dprod();
    printf("Dot product = %d\n", sum);
    return 0;
}

