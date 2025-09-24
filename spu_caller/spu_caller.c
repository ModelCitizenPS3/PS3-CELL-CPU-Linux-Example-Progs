// calling an assembly coded function

#include <stdio.h>

extern int func(int, int);

int main(int argc, char **argv)
{
    int res = func(5, 2);
    printf("Result = %d\n", res);
    return 0;
}

