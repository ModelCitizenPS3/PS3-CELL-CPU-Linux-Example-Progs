    .data
    .align 4

# Create operands for subtraction
reg_20:
    .word 0x70000000, 0x00000000, 0x00000000, 0x00000000
reg_21:
    .word 0x60000000, 0x00000000, 0x00000000, 0x00000001

    .text
    .align 4
    .global _start

_start:
    lqa     $20,reg_20
    lqa     $21,reg_21
    
    bg      $22,$20,$21     # Create the borrow vector
    shlqbyi $22,$22,4       # Shift the borrow vector left
    nor     $22,$22,$22     # Invert the borrow bits
    sfx     $22,$21,$20     # Subtract Reg 21 from Reg 20 using borrow bits in Reg 22
    stop    0

