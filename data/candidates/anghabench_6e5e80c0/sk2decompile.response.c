static unsigned long adjust_stack_addr(unsigned long stack_addr,
                                       unsigned int stack_size) {
  unsigned long adjusted_stack_addr;
  adjusted_stack_addr = stack_addr + (stack_size * 8);
  return adjusted_stack_addr;
}