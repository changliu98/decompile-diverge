char *__cdecl func0(char *text)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; text[i]; ++i )
  {
    if ( text[i] == 32 || text[i] == 44 || text[i] == 46 )
      text[i] = 58;
  }
  return text;
}