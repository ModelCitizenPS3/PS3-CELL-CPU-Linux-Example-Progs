#include <stdio.h>

int main(unsigned long long spe_id, unsigned long long argp, unsigned long long envp)
{
    printf("Hello SPU - My thtread id is %lld\n", spe_id);
    return 0;
}

