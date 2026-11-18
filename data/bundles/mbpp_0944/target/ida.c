int __cdecl func0(const char *text)
{
  int i; // [rsp+Ch] [rbp-14h]

  for ( i = 0; text[i]; ++i )
  {
    if ( ((*__ctype_b_loc())[text[i]] & 0x800) != 0 )
      return i;
  }
  return -1;
}