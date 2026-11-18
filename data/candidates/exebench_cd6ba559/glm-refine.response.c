uintptr_t __cdecl AddUintptr(uintptr_t *val, uintptr_t delta)
{
    return _InterlockedExchangeAdd64((volatile LONG64 *)val, delta) + delta;
}