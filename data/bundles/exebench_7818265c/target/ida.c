int __cdecl xchg(volatile int *addr, int newval)
{
  return _InterlockedExchange(addr, newval);
}