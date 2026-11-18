void __cdecl sync_set_bit(int nr, volatile unsigned __int64 *addr)
{
  _interlockedbittestandset((volatile signed __int32 *)addr, nr);
}