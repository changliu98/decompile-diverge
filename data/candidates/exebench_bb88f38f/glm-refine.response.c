void __cdecl sync_clear_bit(int nr, volatile unsigned __int64 *addr)
{
  _interlockedbittestandreset64((volatile __int64 *)addr, nr);
}