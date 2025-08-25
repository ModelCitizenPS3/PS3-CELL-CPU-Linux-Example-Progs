#include <stdio.h>

/* Set stack_ptr equal to Register 1 */
register volatile unsigned int *stack_ptr asm("1");

int foo(int);
int bar(int);
int baz(int);

/* foo calls bar */
int foo(int fooval)
{
    printf("Foo Stack Ptr: %p\n", stack_ptr);
    return bar(2 * fooval);
}

/* bar calls baz */
int bar(int barval)
{
    printf("Bar Stack Ptr: %p\n", stack_ptr);
    return baz(2 * barval);
}

/* baz returns twice the input */
int baz(int bazval)
{
    printf("Baz Stack Ptr: %p\n", stack_ptr);
    return 2 * bazval;
}

/* main calls foo */
int main(int argc, char **argv)
{
    printf("Main Stack Ptr: %p\n", stack_ptr);
    return foo(2);
}

