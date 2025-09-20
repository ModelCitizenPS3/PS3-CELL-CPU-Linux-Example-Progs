#include <stdio.h>
#include <spu_mfcio.h>

void interrupt_service(void) __attribute__((section(".interrupt")));

volatile unsigned int check_value = 0;

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    unsigned int mask;

    /* Enable interrupt processing */
    spu_ienable();

    /* Read the event mask */
    mask = spu_read_event_mask();

    /* Write to the event mask */
    spu_write_event_mask(MFC_DECREMENTER_EVENT);

    /* Write to the decrementer and begin countdown */
    spu_write_decrementer(10000);

    /* Loop while waiting for interrupt */
    while (check_value == 0);

    /* Restore the event mask */
    spu_write_event_mask(mask);

    return 0;
}

void interrupt_service(void)
{
    int dec = spu_read_decrementer();
    printf("ISR: Decrementer = %d.\n", dec);

    /* End loop in main function */
    check_value = 1;

    /* Acknowledge event detection */
    spu_write_event_ack(MFC_DECREMENTER_EVENT);

    /* Return to main function */
    asm("iret");
}

