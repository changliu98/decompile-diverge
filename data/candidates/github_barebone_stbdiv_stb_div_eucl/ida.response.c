int __cdecl stb_div_eucl(int v1, int v2)
{
  int ecx20; // ecx
  int r; // [rsp+0h] [rbp-14h]
  int q; // [rsp+4h] [rbp-10h]

  if ( v1 < 0 )
  {
    if ( v1 == 0x80000000 )
    {
      if ( v2 < 0 )
      {
        if ( v2 == 0x80000000 )
        {
          q = 1;
          r = 0;
        }
        else
        {
          q = (v2 - v1) / -v2 + 1;
          r = -((v2 - v1) % -v2);
        }
      }
      else
      {
        q = -(-(v2 + v1) / v2) - 1;
        r = -(-(v2 + v1) % v2);
      }
    }
    else if ( v2 < 0 )
    {
      if ( v2 == 0x80000000 )
      {
        q = 1;
        r = v1 - v2;
      }
      else
      {
        q = -v1 / -v2;
        r = -(-v1 % -v2);
      }
    }
    else
    {
      q = -(-v1 / v2);
      r = -(-v1 % v2);
    }
  }
  else
  {
    if ( v2 >= 0 )
      return v1 / v2;
    if ( v2 == 0x80000000 )
    {
      q = 0;
      r = v1;
    }
    else
    {
      q = -(v1 / -v2);
      r = v1 % -v2;
    }
  }
  if ( r >= 0 )
    return q;
  ecx20 = 1;
  if ( v2 > 0 )
    ecx20 = -1;
  return ecx20 + q;
}