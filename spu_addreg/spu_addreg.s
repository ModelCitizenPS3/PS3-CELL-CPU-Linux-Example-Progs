# Create the .data section, aligned on 16-byte boundary
    .data
    .align 4

# Create two constant vectors, addend1 and addend2
addend1:
    .int 0,1,2,3
addend2:
    .int 4,5,6,7

# Create the .text section, aligned on 16-byte boundary
    .text
    .align 4

# Create a global symbol, _start, for linker
    .global _start

# list instructions in the _start procedure
_start:
    lqa     $20,addend1     # Place addend1 in Reg 20
    lqa     $21,addend2     # Place addend2 in Reg 21
    a       $21,$20,$21     # Add Regs 20, 21 => Reg 21
    stop    0

