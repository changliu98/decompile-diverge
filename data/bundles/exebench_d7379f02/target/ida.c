void __cdecl itoa(unsigned __int16 value, char *s)
{
  unsigned __int16 v2; // ax
  unsigned __int16 max; // [rsp+0h] [rbp-24h]
  unsigned __int16 index; // [rsp+2h] [rbp-22h]
  char tmp[16]; // [rsp+4h] [rbp-20h]
  char *sa; // [rsp+14h] [rbp-10h]
  unsigned __int16 valuea; // [rsp+22h] [rbp-2h]

  valuea = value;
  sa = s;
  index = 0;
  if ( value )
  {
    while ( valuea )
    {
      v2 = index++;
      tmp[v2] = valuea % 10 + 48;
      valuea /= 10;
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