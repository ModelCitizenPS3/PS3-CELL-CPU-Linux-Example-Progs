#include <stdio.h>
#include <altivec.h>

/* Create a union of a vector and an array of 16 characters */
typedef union {
    vector unsigned char vec;
    unsigned char scalars[16];
} charVecType;

int main(int argc, char **argv)
{
    int i;
    charVecType charVec;

    /* Initialize the vector elements */
    charVec.vec = (vector unsigned char){'H','e','l','l','o',' ','P','r','o','g','r','a','m','m','e','r'};

    /* Print each element by accessing the array */
    for (i = 0; i < 16; i++)
        printf ("%c", charVec.scalars[i]);
    printf("\n");

    return 0;
}

