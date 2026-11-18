void __cdecl set_bit(int nr, volatile unsigned __int64 *addr)
{
  _bittestandset((signed __int32 *)addr, nr);
}