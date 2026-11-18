bool __cdecl func0(const char *p)
{
  bool v2; // [rsp+3h] [rbp-1Dh]
  int i; // [rsp+4h] [rbp-1Ch]
  char hasSpecial; // [rsp+8h] [rbp-18h]
  bool hasDigit; // [rsp+9h] [rbp-17h]
  bool hasUpper; // [rsp+Ah] [rbp-16h]
  bool hasLower; // [rsp+Bh] [rbp-15h]
  int len; // [rsp+Ch] [rbp-14h]

  len = strlen(p);
  hasLower = 0;
  hasUpper = 0;
  hasDigit = 0;
  hasSpecial = 0;
  if ( len < 6 || len > 12 )
    return 0;
  for ( i = 0; i < len; ++i )
  {
    if ( ((*__ctype_b_loc())[p[i]] & 0x200) != 0 )
    {
      hasLower = 1;
    }
    else if ( ((*__ctype_b_loc())[p[i]] & 0x100) != 0 )
    {
      hasUpper = 1;
    }
    else if ( ((*__ctype_b_loc())[p[i]] & 0x800) != 0 )
    {
      hasDigit = 1;
    }
    else if ( p[i] == 36 || p[i] == 35 || p[i] == 64 )
    {
      hasSpecial = 1;
    }
    else if ( ((*__ctype_b_loc())[p[i]] & 0x2000) != 0 )
    {
      return 0;
    }
  }
  v2 = 0;
  if ( hasLower )
  {
    v2 = 0;
    if ( hasUpper )
    {
      v2 = 0;
      if ( hasDigit )
        return hasSpecial;
    }
  }
  return v2;
}