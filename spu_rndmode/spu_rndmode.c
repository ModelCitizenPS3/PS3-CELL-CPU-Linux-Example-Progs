#include <stdio.h>
#include <spu_intrinsics.h>
#include <simdmath.h>

int main(int argc, char **argv)
{
    vector double vec, result;
    vec = (vector double){7.5, 9.5};

    /* Display rounding before changing the FPSCR */
    result = nearbyintd2(vec);
    printf("Before: %f, %f\n", spu_extract(result, 0), spu_extract(result, 1));

    /* Set Bit 21 of the FPSCR high */
    vector unsigned int fpscr_mask = (vector unsigned int){0x00000400, 0, 0, 0};
    spu_mtfpscr(fpscr_mask);

    /* Display rounding after changing the FPSCR */
    result = nearbyintd2(vec);
    printf("After: %f, %f\n", spu_extract(result, 0), spu_extract(result, 1));
    return 0;
}

