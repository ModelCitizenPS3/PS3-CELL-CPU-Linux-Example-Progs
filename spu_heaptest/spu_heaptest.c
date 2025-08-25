#include <stdio.h>
#include <spu_intrinsics.h>
#include <libmisc.h>

/* Set reg_1 equal to Register 1 */
register volatile vector unsigned int reg_1 asm("1");

int main(int argc, char **argv)
{
    /* Return stack-heap difference before allocation */
    printf("Before allocation: stack - heap = %#x\n", spu_extract(reg_1, 1));

    /* Allocate 16K and display stack-heap difference */
    float *fl_array = malloc_align(0x4000, 7);
    printf("After allocation: stack - heap = %#x\n", spu_extract(reg_1, 1));

    /* Deallocate memory */
    free_align(fl_array);
    return 0;
}

