bool __cdecl func0(const char *text)
{
  int i; // [rsp+8h] [rbp-18h]
  int len; // [rsp+Ch] [rbp-14h]

  len = strlen(text);
  for ( i = 0; i < len / 2; ++i )
  {
    if ( text[i] != text[len - 1 - i] )
      return 0;
  }
  return 1;
}