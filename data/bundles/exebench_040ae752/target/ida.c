int __cdecl test_and_clear_bit(int nr, volatile unsigned __int64 *addr)
{
  return -_bittestandreset((signed __int32 *)addr, nr);
}