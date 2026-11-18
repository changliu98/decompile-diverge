size_t __cdecl itoa(unsigned int value, char *str, unsigned int base)
{
  size_t i; // [rsp+0h] [rbp-68h]
  int index; // [rsp+Ch] [rbp-5Ch]
  size_t current; // [rsp+10h] [rbp-58h]
  char tmp[32]; // [rsp+18h] [rbp-50h]
  char *digits; // [rsp+40h] [rbp-28h]
  unsigned int basea; // [rsp+4Ch] [rbp-1Ch]
  char *stra; // [rsp+50h] [rbp-18h]
  unsigned int valuea; // [rsp+5Ch] [rbp-Ch]

  valuea = value;
  stra = str;
  basea = base;
  digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if ( base < 2 || basea > 0x24 )
    return 0LL;
  if ( valuea )
  {
    current = 0LL;
    while ( valuea )
    {
      index = valuea % basea;
      valuea /= basea;
      tmp[current++] = digits[index];
    }
    for ( i = 0LL; i < current; ++i )
      stra[i] = tmp[current - 1 - i];
    return i;
  }
  else
  {
    *stra = 48;
    return 1LL;
  }
}