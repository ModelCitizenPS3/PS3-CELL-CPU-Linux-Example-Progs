#include <stdio.h>
#include <math.h>
#include <massv.h>

#define N 4

int main(int argc, char **argv)
{
    int i, num;

    /* Initialize the angles */
    float angles[N] = { M_PI / 6, 2 * M_PI / 3, 5 * M_PI / 4, 13 * M_PI / 8 };

    /* Compute the cosines and sines */
    num = N;
    float _Complex coords[N];
    vscosisin(coords, angles, &num);

    /* Compute and display the rectangular coordinates */
    for (i = 0; i < N; i++)
        printf("(%f, %fi)\n", creal(coords[i]), cimag(coords[i]));
    return 0;
}

