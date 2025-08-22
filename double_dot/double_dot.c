#include <stdio.h>
#include <pthread.h>

#define N 1000

int vec1[N], vec2[N], sum[2];

/* Compute the odd or even dot product */
void *dprod(void *ptr)
{
    int i, index = *((int *)ptr);

    sum[index] = 0;
    for (i = index; i < N; i += 2)
        sum[index] += vec1[i] * vec2[i];

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    int i;
    pthread_t threads[2];

    /* Initialize arrays */
    for (i = 0; i < N; i++) {
        vec1[i] = i;
        vec2[i] = N - i;
    }

    /* Create threads to execute dot procuct */
    int index0 = 0;
    int index1 = 1;
    pthread_create(&threads[0], NULL, dprod, (void *)&index0);
    pthread_create(&threads[1], NULL, dprod, (void *)&index1);

    /* Wait for threads to finish */
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    /* Add the result from each thread */
    printf("Dot product = %d\n", (sum[0] + sum[1]));
    return 0;
}

