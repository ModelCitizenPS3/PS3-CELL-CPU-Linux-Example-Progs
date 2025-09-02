#include <stdio.h>
#include <spu_mfcio.h>

#define TAG 3

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    /*The memory location to be read */
    int *result;
    result = (int *)0x10000;

    /* The value to be transferred */
    int check_value[4] __attribute__((aligned(16)));
    int i;
    for (i = 0; i < 4; i++)
        check_value[i] = 42;

    /* Transfer data to other SPE's LS */
    mfc_put(check_value, argp + (unsigned long long)result, sizeof(check_value), TAG, 0, 0);

    /* Wait for the transfer to finish */
    mfc_write_tag_mask(1 << TAG);
    mfc_read_tag_status_all();

    /* Check for updated result */
    while (*result != 42);
    printf("SPE %llu received the message.\n", speid);
    return 0;
}

