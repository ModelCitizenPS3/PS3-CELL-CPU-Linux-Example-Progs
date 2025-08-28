#include <stdio.h>
#include <spu_intrinsics.h>
#include <simdmath.h>

int main(int argc, char **argv)
{
    vector double vec = (vector double){-16e-15, 16e15};
    vector signed int *fr_int;
    vector double fr_frac, mod_frac, *mod_int;

    /* Compute the integer and fraction parts */
    mod_frac = modfd2(vec, mod_int);
    printf("modfd2:\n");
    printf("Integer part: %e, Fraction part: %e\n", spu_extract(*mod_int, 0), spu_extract(mod_frac, 0));
    printf("Integer part: %e, Fraction part: %e\n", spu_extract(*mod_int, 1), spu_extract(mod_frac, 1));

    /* Compute the base and exponent parts */
    fr_frac = frexpd2(vec, fr_int);
    printf("\nfrexpd2:\n");
    printf("Base: %f, Exponent: %d\n", spu_extract(fr_frac, 0), spu_extract(*fr_int, 1));
    printf("Base: %f, Exponent: %d\n", spu_extract(fr_frac, 1), spu_extract(*fr_int, 3));
    return 0;
}

