char *__cdecl func0(const char *str1, char *char_replacement)
{
  char v2; // dl
  int v3; // eax
  int i; // [rsp+0h] [rbp-18h]
  int j; // [rsp+4h] [rbp-14h]

  j = 0;
  for ( i = 0; str1[i]; ++i )
  {
    if ( str1[i] == 32 )
      v2 = *char_replacement;
    else
      v2 = str1[i];
    v3 = j++;
    func0_str2[v3] = v2;
  }
  func0_str2[j] = 0;
  return func0_str2;
}