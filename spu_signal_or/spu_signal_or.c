#include <stdio.h>
#include <spu_mfcio.h>

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    unsigned int sig_content;

    /* Block until the confirmation signal arrives */
    spu_read_signal2();

    /* Read the data signals and display the ORed content */
    sig_content = spu_read_signal1();
    printf("Received signal = %x\n", sig_content);
    return 0;
}

