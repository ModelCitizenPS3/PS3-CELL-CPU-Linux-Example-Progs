#include <stdio.h>
#include <spu_mfcio.h>
#include <libisolation.h>

int main()
{
    /* data to be sent */
    vector unsigned int msg;

    /* address of the data */
    unsigned long long ea;
    unsigned int i, ea_low, ea_high;

    /* Create effective address from mailbox data */
    ea_low = spu_read_in_mbox();
    ea_high = spu_read_in_mbox();
    ea = mfc_hl2ea(ea_high, ea_low);

    /* Access the data from main memory and copy it to the LS */
    if (copyin(ea, &msg, sizeof(msg)) != 0)
        return -1;

    /* Display vector contents */
    printf("Result: ");
    for (i = 0; i < 4; i++)
        printf("%u ", spu_extract(msg, i));
    printf("\n");

    return 0;
}

