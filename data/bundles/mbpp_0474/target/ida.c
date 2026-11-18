char *__cdecl func0(char *str1, char ch_0, char newch)
{
  int i; // [rsp+10h] [rbp-10h]

  strcpy(func0_str2, str1);
  for ( i = 0; i < strlen(func0_str2); ++i )
  {
    if ( func0_str2[i] == ch_0 )
      func0_str2[i] = newch;
  }
  return func0_str2;
}