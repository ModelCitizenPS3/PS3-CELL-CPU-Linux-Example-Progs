    .text
    .align 4
    .global _start

_start:
    # Load values into Registers 3 & 4
    il      $3,5
    il      $4,2

    # Branch to func
    brsl    $lr,func

    stop    0

