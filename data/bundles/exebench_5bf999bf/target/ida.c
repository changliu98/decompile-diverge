void __cdecl clear_bit(int nr, volatile unsigned __int64 *addr)
{
  _bittestandreset((signed __int32 *)addr, nr);
}