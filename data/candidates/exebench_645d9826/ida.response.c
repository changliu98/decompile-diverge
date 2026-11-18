char *__cdecl byte2bin(char in, char *out)
{
  char v2; // al
  int n; // [rsp+0h] [rbp-14h]

  for ( n = 0; n < 8; ++n )
  {
    v2 = 49;
    if ( ((1 << (7 - n)) & in) == 0 )
      v2 = 48;
    out[n] = v2;
  }
  out[8] = 0;
  return out;
}