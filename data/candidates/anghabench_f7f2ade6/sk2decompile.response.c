static inline int pmc_overflow(unsigned long val) {
  if (val & 0x80000000)
    return 1;
  else
    return 0;
}