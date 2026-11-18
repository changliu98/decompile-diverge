uintptr_t __cdecl AddUintptr(uintptr_t *val, uintptr_t delta)
{
  return delta + _InterlockedExchangeAdd64((volatile signed __int64 *)val, delta);
}