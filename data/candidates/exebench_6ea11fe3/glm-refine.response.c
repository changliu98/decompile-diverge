void __cdecl sync_set_bit(int nr, volatile unsigned __int64 *addr)
{
  _interlockedbittestandset64((volatile __int64 *)addr, nr);
}