unsigned int __cdecl bcd2int(unsigned __int8 *s, int slen)
{
  int i; // [rsp+8h] [rbp-1Ch]
  int o; // [rsp+Ch] [rbp-18h]

  if ( slen > 5 )
    return 0;
  o = 0;
  for ( i = 0; i < slen; ++i )
    o = s[i] % 16 + 10 * (s[i] / 16) + 100 * o;
  return o;
}