void __cdecl sync_clear_bit(int nr, volatile unsigned __int64 *addr)
{
  _interlockedbittestandreset((volatile signed __int32 *)addr, nr);
}