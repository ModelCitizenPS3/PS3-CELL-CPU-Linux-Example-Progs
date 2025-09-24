    .text
    .align 4
    .global func
    .type func, %function

func:
    # Decrement the stack to store two local variables
    stqd    $sp,-48($sp)
    ai      $sp,$sp,-48

    # Add the input values together and store the sum on the stack
    a       $2,$3,$4
    stqd    $2,32($sp)

    # Subtract the input values and store the difference on the stack
    sf      $2,$4,$3
    stqd    $2,16($sp)

    # Retrieve the sum and difference from the stack and multiply
    lqd     $3,32($sp)
    lqd     $2,16($sp)
    mpy     $3,$2,$3

    # Increment the stack and return to the link address
    ai      $sp,$sp,48
    bi      $lr

