unsigned_long adjust_stack_addr(unsigned_long addr,uint n)

{
  uint n_local;
  unsigned_long addr_local;
  
  return addr + (ulong)n * 8;
}