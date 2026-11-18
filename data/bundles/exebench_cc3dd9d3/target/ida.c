void __cdecl AssignBit(unsigned __int64 *array, int bit, int value)
{
  unsigned __int64 v3; // rcx
  unsigned __int64 v4; // rdx
  unsigned __int64 mask; // [rsp+0h] [rbp-18h]

  mask = 1LL << (bit & 0x3F);
  v3 = (unsigned __int64)bit >> 6;
  if ( value )
    v4 = array[v3] | mask;
  else
    v4 = array[v3] & ~mask;
  array[v3] = v4;
}