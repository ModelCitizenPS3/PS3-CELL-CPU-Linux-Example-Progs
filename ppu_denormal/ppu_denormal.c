#include <stdio.h>
#include <altivec.h>

int main(int argc, char **argv)
{
    vector unsigned short old_vscr, new_vscr, mask;
    old_vscr = vec_mfvscr();
    mask = (vector unsigned short){0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xfeff, 0xffff};
    new_vscr = vec_and(old_vscr, mask);
    vec_mtvscr(new_vscr);
    vector float denormals, zeroes;

    /* A vector containing four denormal values */
    denormals = (vector float){5.9e-40, 5.9e-40, 5.9e-40, 5.9e-40};

    zeroes = (vector float){0.0, 0.0, 0.0, 0.0};

    /* Compare the denormal values to zero */
    printf("Result: %d\n", vec_all_eq(denormals, zeroes));

    return 0;
}

