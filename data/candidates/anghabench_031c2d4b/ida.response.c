bool __cdecl tomoyo_invalid(const unsigned __int8 c)
{
  bool v2; // [rsp+1h] [rbp-3h]
  bool v3; // [rsp+2h] [rbp-2h]

  v3 = 0;
  if ( c )
  {
    v2 = 1;
    if ( c > 0x20u )
      return c >= 0x7Fu;
    return v2;
  }
  return v3;
}