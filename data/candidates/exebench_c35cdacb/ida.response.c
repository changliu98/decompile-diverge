int __cdecl libbf_is_composed_poweroftwo(unsigned int number, int *shift1, int *shift2)
{
  int count; // [rsp+0h] [rbp-20h]
  int i; // [rsp+4h] [rbp-1Ch]
  unsigned int numbera; // [rsp+18h] [rbp-8h]

  numbera = number;
  i = 0;
  count = 0;
  if ( !number )
    return 0;
  if ( shift1 )
    *shift1 = 0;
  if ( shift2 )
    *shift2 = 0;
  while ( numbera )
  {
    if ( (numbera & 1) != 0 )
    {
      if ( ++count == 1 )
      {
        if ( shift1 )
          *shift1 = i;
      }
      else
      {
        if ( count != 2 )
          return 0;
        if ( shift2 )
          *shift2 = i;
      }
    }
    ++i;
    numbera >>= 1;
  }
  return 1;
}