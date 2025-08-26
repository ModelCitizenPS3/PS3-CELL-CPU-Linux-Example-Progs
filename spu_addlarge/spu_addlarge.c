#include <stdio.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv)
{
    int i;
    vector unsigned int sum, carry;
    vector unsigned int add1 = (vector unsigned int){0x80000000, 0x80000000, 0x80000000, 0x80000000};
    vector unsigned int add2 = (vector unsigned int){0x1fffffff, 0x7fffffff, 0x7fffffff, 0x80000000};

    /* Step 1: Obtain the initial carry vector */
    carry = spu_genc(add1, add2);

    /* Step 2: Shift the carry left and find the new carry vector */
    carry = spu_slqwbyte(carry, sizeof(unsigned int));
    carry = spu_gencx(add1, add2, carry);

    /* Step 3: Shift the carry left and find the new carry vector */
    carry = spu_slqwbyte(carry, sizeof(unsigned int));
    carry = spu_gencx(add1, add2, carry);

    /* Step 4: Shift the carry left and add the vectors */
    carry = spu_slqwbyte(carry, sizeof(unsigned int));
    sum = spu_addx(add1, add2, carry);

    for (i = 0; i < 4; i++)
        printf("%08x ", spu_extract(sum, i));
    printf("\n");

    return 0;
}

