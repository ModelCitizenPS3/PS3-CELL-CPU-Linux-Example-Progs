#include <stdio.h>
#include <spu_mfcio.h>

void interrupt_service(void) __attribute__((section (".interrupt")));

volatile unsigned int check_value = 0;

int main(unsigned long long speid, unsigned long long argp, unsigned long long argv)
{
    unsigned int mbox_content;

    /* Write to the event mask */
    spu_write_event_mask(MFC_IN_MBOX_AVAILABLE_EVENT);

    /* Enable interrupt processing and wait */
    spu_ienable();
    while (!check_value);

    /* Read mailbox and display result */
    mbox_content = spu_read_in_mbox();
    printf("Received data = %x\n", mbox_content);
    return 0;
}

void interrupt_service(void)
{
    spu_write_event_ack(MFC_IN_MBOX_AVAILABLE_EVENT);
    check_value++;
    asm("iret");
}

