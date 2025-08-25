#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <altivec.h>

#define N 16

/* Replace the frirst input by the max, the second input by the min */
#define MINMAX(max, min) { temp = vec_min(max, min); max = vec_max(max, min); min = temp; }

void sort_vectors(int *);
void sort_elements(int *);

int main(int argc, char **argv)
{
    int sortVec[N] __attribute__((aligned(16)));
    int i;

    /* Generate array elements with the pid */
    srand(getpid());
    for (i = 0; i < N; i++)
        sortVec[i] = rand() % N;

    /* Display the initial values */
    for (i = 0; i < N; i++)
        printf("%d ", sortVec[i]);
    printf("\n");

    /* Sort the values in the array */
    sort_vectors(sortVec);
    sort_elements(sortVec);

    /* Display the sorted values */
    for (i = 0; i < N; i++)
        printf("%d ", sortVec[i]);
    printf("\n");
    return 0;
}

/* Perform inter-vector sort */
void sort_vectors(int *array)
{
    int i, j, numVec = N / 4;   /* Number of vectors */
    vector signed int max, min, temp, temp_max;
    vector unsigned char indexVec = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3 };

    for (i = 1; i < numVec; i++) {

        /* Assume the first value is largest */
        max = vec_ld(i * sizeof(max), array);
        for (j = i; j > 0; j--) {
            temp_max = max;
            min = vec_ld((j - 1) * sizeof(min), array);

            /* Obtain the min/max elements */
            MINMAX(max, min);
            max = vec_perm(max, min, indexVec);
            MINMAX(max, min);
            max = vec_perm(max, min, indexVec);
            MINMAX(max, min);
            max = vec_perm(max, min, indexVec);
            MINMAX(max, min);
            max = vec_perm(max, min, indexVec);

            vec_st(max, j * sizeof(max), array);
            if (vec_any_ne(max, temp_max)) {
                if (j > 1)
                    max = min;
                else
                    vec_st(min, 0, array);
            }
            else
                break;
        }
    }
}

/* Perform intra-vector sort */
void sort_elements(int *array)
{
    int i, numVec = N / 4;      /* Number of vectors */

    /* Vectors used in the first compare-arrange */
    vector unsigned char perm_reverse = { 12, 13, 14, 15, 8, 9, 10, 11, 4, 5, 6, 7, 0, 1, 2, 3 };
    vector unsigned char add_index1 = { 12, 12, 12, 12, 4, 4, 4, 4, 4, 4, 4, 4, 12, 12, 12, 12 };
    vector unsigned char basis_index1 = { 0, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6, 7, 0, 1, 2, 3 };

    /* Vectors used in the second compare-arrange */
    vector unsigned char perm_in_out = { 4, 5, 6, 7, 0, 1, 2, 3, 12, 13, 14, 15, 8, 9, 10, 11};
    vector unsigned char add_index2 = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
    vector unsigned char basis_index2 = { 0, 1, 2, 3, 0, 1, 2, 3, 8, 9, 10, 11, 8, 9, 10, 11};

    /* Vectors used in the third compare-arrange */
    vector unsigned char perm_middle = { 0, 1, 2, 3, 8, 9, 10, 11, 4, 5, 6, 7, 12, 13, 14, 15 };
    vector unsigned char add_index3 = { 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0 };
    vector unsigned char basis_index3 = { 0, 1, 2, 3, 4, 5, 6, 7, 4, 5, 6, 7, 12, 13, 14, 15 };

    vector bool int mask;
    vector unsigned char pattern;

    /* The intra-vector sort */
    for (i = 0; i < numVec; i++) {
        vector signed int vec = vec_ld(i * sizeof(vec), array);

        /* First compare and rearrange */
        mask = vec_cmpgt(vec, vec_perm(vec, vec, perm_reverse));
        pattern = vec_and((vector unsigned char)mask, add_index1);
        pattern = vec_add(pattern, basis_index1);
        vec = vec_perm(vec, vec, pattern);

        /* Second compare and rearrange */
        mask = vec_cmpgt(vec, vec_perm(vec, vec, perm_in_out));
        pattern = vec_and((vector unsigned char)mask, add_index2);
        pattern = vec_add(pattern, basis_index2);
        vec = vec_perm(vec, vec, pattern);

        /* Third compare and rearrange */
        mask = vec_cmpgt(vec, vec_perm(vec, vec, perm_middle));
        pattern = vec_and((vector unsigned char)mask, add_index3);
        pattern = vec_add(pattern, basis_index3);
        vec = vec_perm(vec, vec, pattern);

        vec_st(vec, i * sizeof(vec), array);
    }
}

