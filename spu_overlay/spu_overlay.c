#include <stdio.h>
#include <spu_intrinsics.h>

/*nDeclare functions in overlay1.o and overlay2.o */
extern vector unsigned int reverse_vector(vector unsigned int);
extern vector unsigned int reverse_again(vector unsigned int);

int main(unsigned long long speid, unsigned long long argp, unsigned long long envp)
{
    vector unsigned int test_vec = (vector unsigned int){0, 1, 2, 3};
    
    printf("Calling the overlay functions:\n");

    /* Call the external functions */
    test_vec = reverse_vector(test_vec);
    test_vec = reverse_again(test_vec);

    return 0;
}

