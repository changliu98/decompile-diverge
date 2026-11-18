int __cdecl sync_test_and_set_bit(int nr, volatile unsigned __int64 *addr)
{
  return -(unsigned __int8)_interlockedbittestandset((volatile signed __int32 *)addr, nr);
}