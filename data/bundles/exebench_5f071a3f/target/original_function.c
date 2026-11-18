void
StoreUintptr (uintptr_t *addr, uintptr_t val)
{
  uintptr_t v;

  v = *addr;
  while (! __sync_bool_compare_and_swap (addr, v, val))
    v = *addr;
}