#include <stdio.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv)
{
    int i;
    vector unsigned short test_vec = (vector unsigned short){2, 4, 6, 8, 10, 12, 14, 16};

    /* Compare the vector elements to 11 */
    test_vec = spu_cmpgt(test_vec, 11);

    /* Display the compare result */
    printf("The compare result is: ");
    for (i = 0; i < 8; i++)
        printf("%04x ", spu_extract(test_vec, i));

    /* Display the gathered LSBs */
    printf("\nThe concatenated LSBs form: %#x\n", spu_gather(test_vec));
    return 0;
}

