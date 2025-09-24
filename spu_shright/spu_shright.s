    .data
    .align 4

# Immediate value to be shifted
reg_20:
    .word 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA

# Declare the text section
    .text
    .align 4
    .global _start

_start:
    lqa         $20,reg_20      # Load immediate value into $20

    rotmi       $21,$20,-7      # Shift bits in words right
    rotqmbii    $22,$20,-7      # Shift entire quadword right
    rotmai      $23,$20,-7      # Shift bits in words right and repeat sign bit

    stop        0

