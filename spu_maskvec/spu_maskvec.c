#include <stdio.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv)
{
    int i;
    vector unsigned int all_ones = (vector unsigned int){0xFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF, 0XFFFFFFFF};
    vector unsigned int all_zeroes = (vector unsigned int){0x00000000, 0X00000000, 0X00000000, 0X00000000};

    /* These bits will form the selection mask */
    unsigned short mask = 0x9;

    /* Each bit in 0x9 forms a word in the mask */
    vector unsigned int resultw = spu_sel(all_zeroes, all_ones, spu_maskw(mask));
    printf("resultw: ");
    for (i = 0; i < 4; i++)
        printf("%08x", spu_extract(resultw, i));

    /* Each bit in 0x09 forms a halfword in the mask */
    vector unsigned short resulth = spu_sel((vector unsigned short)all_zeroes, (vector unsigned short)all_ones, spu_maskh(mask));
    printf("\nresulth: ");
    for (i = 0; i < 8; i++)
        printf("%04x", spu_extract(resulth, i));

    /* Each bit in 0x0009 forms a byte in the mask */
    vector unsigned char resultb = spu_sel((vector unsigned char)all_zeroes, (vector unsigned char)all_ones, spu_maskb(mask));
    printf("\nresultb: ");
    for (i = 0; i < 16; i++)
        printf("%02x", spu_extract(resultb, i));
    printf("\n");
    return 0;
}

