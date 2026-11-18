static inline int uasm_in_compat_space_p(unsigned long addr) {
  unsigned long gs;
  asm volatile("mov %0, %%gs:0" : "=r"(gs) : : "memory");
  return addr == gs;
}