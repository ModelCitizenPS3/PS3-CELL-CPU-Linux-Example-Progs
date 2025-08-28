#include <stdio.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv)
{
    vector float test1, test2, result;

    /* Check initial value of FPSCR */
    vector unsigned int reg = spu_mffpscr();
    printf("FPSCR Before: %x %x %x %x\n", spu_extract(reg, 0), spu_extract(reg, 1), spu_extract(reg, 2), spu_extract(reg, 3));

    /* Produce an underflow (UNF) error */
    test1 = (vector float){0, 2e-38, 0, 0};
    test2 = (vector float){.5, .5, .5, .5};
    result = spu_mul(test1, test2);

    /* Check the updated value of the FPSCR */
    reg = spu_mffpscr();
    printf("FPSCR After: %x %x %x %x\n", spu_extract(reg, 0), spu_extract(reg, 1), spu_extract(reg, 2), spu_extract(reg, 3));
    return 0;
}

