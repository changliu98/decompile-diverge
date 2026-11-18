unsigned_long it_advance(unsigned_long cpsr)

{
  unsigned_long it;
  unsigned_long mask;
  unsigned_long cpsr_local;
  
  if ((cpsr & 0x6000400) == 0) {
    cpsr_local = (PSR_IT_MASK ^ 0xffffffffffffffff) & cpsr;
  }
  else {
    cpsr_local = ((cpsr & 0x6001c00) >> 0x10 | (cpsr & 0x6001c00) << 1) & 0x6001c00 |
                 cpsr & 0xfffffffff9ffe3ff;
  }
  return cpsr_local;
}