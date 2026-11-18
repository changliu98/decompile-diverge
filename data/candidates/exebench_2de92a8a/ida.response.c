int __cdecl sprint_int_number_nonlocalized(char *str, int q, int minimum, int sign)
{
  int v4; // ecx
  int v5; // ecx
  int base; // [rsp+0h] [rbp-28h]
  int j; // [rsp+4h] [rbp-24h]
  int i; // [rsp+8h] [rbp-20h]
  int z; // [rsp+Ch] [rbp-1Ch]
  int flag; // [rsp+10h] [rbp-18h]
  int minimuma; // [rsp+18h] [rbp-10h]
  int qa; // [rsp+1Ch] [rbp-Ch]

  qa = q;
  minimuma = minimum;
  flag = 0;
  j = 0;
  base = 1000000000;
  if ( minimum < 0 )
    minimuma = 0;
  if ( minimuma > 9 )
    flag = 1;
  if ( q >= 0 )
  {
    if ( sign )
    {
      j = 1;
      *str = 43;
    }
  }
  else
  {
    j = 1;
    *str = 45;
    qa = -q;
  }
  for ( i = 10; i; --i )
  {
    if ( minimuma == i )
      flag = 1;
    z = qa / base;
    qa %= base;
    if ( z || flag )
    {
      v4 = j++;
      str[v4] = z + 48;
      flag = 1;
    }
    base /= 10;
  }
  if ( !flag )
  {
    v5 = j++;
    str[v5] = 48;
  }
  str[j] = 0;
  return j;
}