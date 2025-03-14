// memory-mapped I/O addresses
# GPIO_SWs   = 0x80001400
# GPIO_LEDs  = 0x80001404
# GPIO_INOUT = 0x80001408
.globl main

.data
  delay_time: .word 10000000

.text   
main:
  li t0, 0x80001400
  li t1, 0xFFFF
  sw t1, 8(t0) # GPIO_INOUT = 0xFFFF

repeat:
  lw   t1, 0(t0)      # read switches: t1 = GPIO_SWs
  srli t1, t1, 16     # shift val to the right by 16 bits 
  sw   t1, 4(t0)      # write value to LEDs: GPIO_LEDs = t1
  lw   t2, delay_time # load delay time
  jal  delay          # jump to delay
  sw   zero, 4(t0)    # turn off LEDs
  lw   t2, delay_time # load delay time again
  jal  ra, delay      # delay again
  j    repeat         # repeat loop

delay:
  addi t2, t2, -1     # decrement delay counter
  bnez t2, delay      # repeat until t2 == 0
  ret
