int __cdecl test_and_change_bit(int nr, volatile unsigned __int64 *addr)
{
  return -_bittestandcomplement((signed __int32 *)addr, nr);
}