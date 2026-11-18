int __cdecl test_and_change_bit(long nr, volatile unsigned __int64 *addr)
{
  return _bittestandcomplement64((signed __int64 *)addr, nr) != 0;
}