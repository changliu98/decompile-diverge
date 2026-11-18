int uasm_in_compat_space_p(long addr)

{
  long addr_local;
  
  return (int)(addr == (int)addr);
}