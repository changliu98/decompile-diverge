void __cdecl StoreUintptr(uintptr_t *addr, uintptr_t val)
{
  signed __int64 v; // [rsp+0h] [rbp-18h]

  for ( v = *addr; v != _InterlockedCompareExchange64((volatile signed __int64 *)addr, val, v); v = *addr )
    ;
}