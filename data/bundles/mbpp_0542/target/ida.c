char *__cdecl func0(const char *text)
{
  int i; // [rsp+4h] [rbp-Ch]

  strcpy(func0_result, text);
  for ( i = 0; func0_result[i]; ++i )
  {
    if ( func0_result[i] == 32 || func0_result[i] == 44 || func0_result[i] == 46 )
      func0_result[i] = 58;
  }
  return func0_result;
}