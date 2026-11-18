int __cdecl memcasecmp(const void *vs1, const void *vs2, size_t n)
{
  int diff; // [rsp+8h] [rbp-48h]
  int U1; // [rsp+10h] [rbp-40h]
  unsigned __int8 u2; // [rsp+16h] [rbp-3Ah]
  size_t i; // [rsp+18h] [rbp-38h]

  for ( i = 0LL; i < n; ++i )
  {
    u2 = *((_BYTE *)vs2 + i);
    U1 = toupper(*((unsigned __int8 *)vs1 + i));
    diff = U1 - toupper(u2);
    if ( diff )
      return diff;
  }
  return 0;
}