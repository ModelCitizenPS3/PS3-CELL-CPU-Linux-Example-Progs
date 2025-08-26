#include <stdio.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv)
{
    int i;

    /* Set elements in vector to zero */
    vector unsigned int vec = (vector unsigned int)spu_splats(0);

    /* Insert '5' into the third position */
    vec = spu_insert(5, vec, 2);

    for (i = 0; i < 4; i++)
        printf("%u ", spu_extract(vec, i));
    printf("\n");
    return 0;
}

