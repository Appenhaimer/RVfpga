// memory-mapped I/O addresses
# GPIO_SWs   = 0x80001400
# GPIO_LEDs  = 0x80001404
# GPIO_INOUT = 0x80001408
.globl main

main:
  li t0, 0x80001400
  li t1, 0xFFFF
  sw t1, 8(t0)

repeat:
  lw   t1, 0(t0)      # read switches: t1 = GPIO_SWs
  srli t1, t1, 16     # shift val to the right by 16 bits
  not  t1, t1         # invert the bits
  sw   t1, 4(t0)      # write value to LEDs: GPIO_LEDs = t1
  j    repeat         # repeat loop
