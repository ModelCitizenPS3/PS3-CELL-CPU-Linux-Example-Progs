#include <stdio.h>
#include <spu_intrinsics.h>
#include <simdmath.h>

int main(int argc, char **argv)
{
    /* Initialize the test vector */
    vector float vec = (vector float){-2.5e20, -2.5, 2.5, 2.5e20};

    /* Display the rounded values as signed long longs */
    llroundf4_t ans = llroundf4(vec);
    printf("Rounded value of %f = %lld\n", spu_extract(vec, 0), spu_extract(ans.vll[0], 0));
    printf("Rounded value of %f = %lld\n", spu_extract(vec, 1), spu_extract(ans.vll[0], 1));
    printf("Rounded value of %f = %lld\n", spu_extract(vec, 2), spu_extract(ans.vll[1], 0));
    printf("Rounded value of %f = %lld\n", spu_extract(vec, 3), spu_extract(ans.vll[1], 1));
    return 0;
}

