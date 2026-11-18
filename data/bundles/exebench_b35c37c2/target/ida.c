void __cdecl itox(unsigned __int16 value, char *s)
{
  unsigned __int16 v2; // ax
  unsigned __int16 v; // [rsp+0h] [rbp-26h]
  unsigned __int16 max; // [rsp+2h] [rbp-24h]
  unsigned __int16 index; // [rsp+4h] [rbp-22h]
  char tmp[16]; // [rsp+6h] [rbp-20h]
  char *sa; // [rsp+16h] [rbp-10h]
  unsigned __int16 valuea; // [rsp+24h] [rbp-2h]

  valuea = value;
  sa = s;
  index = 0;
  if ( value )
  {
    while ( valuea )
    {
      v = valuea % 16;
      v2 = index++;
      if ( v >= 0xAu )
        tmp[v2] = v - 10 + 97;
      else
        tmp[v2] = v + 48;
      valuea /= 16;
    }
    max = index;
    while ( index )
    {
      sa[max - index] = tmp[index - 1];
      --index;
    }
    sa[max] = 0;
  }
  else
  {
    *sa = 48;
    sa[1] = 0;
  }
}