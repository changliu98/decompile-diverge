bool
uasm_in_compat_space_p (void *addr)
{
  return ((uintptr_t) addr == (uint32_t) addr);
}