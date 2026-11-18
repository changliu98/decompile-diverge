int __cdecl str_to_int(char *str, int *num)
{
  int digit; // [rsp+0h] [rbp-24h]
  int r; // [rsp+4h] [rbp-20h]
  int i; // [rsp+8h] [rbp-1Ch]

  i = 0;
  r = 10;
  *num = 0;
  if ( __PAIR64__(str[1], *str) == 0x7800000030LL )
  {
    i = 2;
    r = 16;
  }
  if ( !str[i] )
    return -1;
  while ( str[i] )
  {
    if ( str[i] < 48 || str[i] > 57 )
    {
      if ( r == 16 && str[i] >= 65 && str[i] <= 70 )
      {
        digit = str[i] - 65 + 10;
      }
      else
      {
        if ( r != 16 || str[i] < 97 || str[i] > 102 )
          return -1;
        digit = str[i] - 97 + 10;
      }
    }
    else
    {
      digit = str[i] - 48;
    }
    *num = digit + r * *num;
    ++i;
  }
  return 0;
}