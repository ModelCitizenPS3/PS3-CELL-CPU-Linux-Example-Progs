#include <stdio.h>
#include <spu_mfcio.h>

#define TAG 31

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    /* The LS buffer that holds the data */
    unsigned char asc[128] __attribute__((aligned(128)));

    /* Thansfer the array from argp to asc */
    mfc_get(asc, argp, sizeof(asc), TAG, 0, 0);

    /* Tell the MFC which tag group to monitor */
    mfc_write_tag_mask(1 << TAG);

    /* Wait for tag group to finish its transfer */
    mfc_read_tag_status_all();

    printf("%c%c%c%c%c %c%c%c%c%c%c\n", asc[72], asc[101], asc[108], asc[108], asc[111], asc[87], asc[111], asc[114], asc[108], asc[100], asc[33]);
    return 0;
}

