#include <stdio.h>

int main(unsigned long long spe_id, unsigned long long argp, unsigned long long envp)
{
    printf("Hello SPU! The value of argp is %lld\n", argp);
    return 0;
}

