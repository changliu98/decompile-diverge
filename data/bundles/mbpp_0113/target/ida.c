int __cdecl func0(const char *text)
{
  int i; // [rsp+8h] [rbp-18h]
  int ia; // [rsp+8h] [rbp-18h]
  int len; // [rsp+Ch] [rbp-14h]
  const char *texta; // [rsp+10h] [rbp-10h]

  texta = text;
  len = strlen(text);
  while ( *texta == 32 )
  {
    ++texta;
    --len;
  }
  if ( len < 1 )
    return -1;
  if ( *texta == 43 || *texta == 45 )
  {
    for ( i = 1; i < len; ++i )
    {
      if ( texta[i] < 48 || texta[i] > 57 )
        return 0;
    }
    return 1;
  }
  else
  {
    for ( ia = 0; ia < len; ++ia )
    {
      if ( texta[ia] < 48 || texta[ia] > 57 )
        return 0;
    }
    return 1;
  }
}