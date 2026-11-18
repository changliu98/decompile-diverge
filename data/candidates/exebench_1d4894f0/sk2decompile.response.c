void stack4_replace_top(unsigned long *stack, unsigned long new_top) {
  unsigned long s = *stack;
  s &= ~0x000000000000000fUL;
  s |= new_top;
  *stack = s;
}