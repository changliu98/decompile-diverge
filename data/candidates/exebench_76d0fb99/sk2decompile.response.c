void stack4_push(unsigned long *stack, unsigned long value) {
  unsigned long s = *stack;
  s <<= 4;
  s |= value;
  *stack = s;
}