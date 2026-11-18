void
StoreUintptr (uintptr_t *addr, uintptr_t val)
{
  uintptr_t oldval, newval;

  do
    {
      LOCK ();
      oldval = *addr;
      newval = oldval;
      if (oldval == newval)
 *addr = val;
      UNLOCK ();
    }
  while (oldval != newval);
}