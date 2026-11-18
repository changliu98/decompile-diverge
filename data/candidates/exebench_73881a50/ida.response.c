int __cdecl test_and_set_bit(int nr, volatile unsigned __int64 *addr)
{
  return -_bittestandset((signed __int32 *)addr, nr);
}