#include <stdio.h>
#include <math.h>
#include <massv.h>

#define N 60

int main(int argc, char **argv)
{
    int i;
    int num = N;
    float angles[N], sines[N];

    /* Generate sixty angles in radians */
    for (i = 0; i < N; i++)
        angles[i] = 2 * M_PI * i / N;

    /* Compute the sines */
    vssin(sines, angles, &num);

    /* Display the results */
    printf("Sines:\n");
    for (i = 0; i < N; i++)
        printf("%f\n", sines[i]);
    return 0;
}

