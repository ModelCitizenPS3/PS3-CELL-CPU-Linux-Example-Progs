#include <stdio.h>
#include "profile.h"

#define N 250

int main()
{
    int i, j;
    unsigned int num_array[N + 1];
    num_array[0] = num_array[1] = 1;

    /* Insert checkpoints */
    prof_cp0();     /* Clear statistics */
    prof_cp30();    /* Start collecting statistics */

    /* Set i^2 and further multiples of i to 1 */
    for (i = 2; i * i <= N; i++) {
        if (num_array[i] == 0) {
            for (j = i * i; j <= N; j += i)
                num_array[j] = 1;
        }
    }

    prof_cp31();    /* Stop collecting statistics */

    /* Display indices of prime numbers */
    printf("Prime numbers less than %u: ", N);
    for (i = 2; i <= N; i++) {
        if (num_array[i] != 1)
            printf("%u ", i);
    }
    printf("\n");

    return 0;
}

