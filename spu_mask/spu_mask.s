    .data
    .align 4

# Create shufb arguments, reg_a and reg_b
reg_a:
    .byte 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30
reg_b:
    .byte 32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62

    .text
    .align 4
    .global _start

_start:
    il      $20,0x07        # Load 7 into each word of R20
    cbd     $21,0($20)      # Create mask (rc) for shufb

    lqa     $22,reg_a       # Create ra for shufb
    lqa     $23,reg_b       # Create rb for shufb

    shufb   $24,$22,$23,$21 # Use R21 to select values
    stop    0

