char *__cdecl func0(const char *str1)
{
  int v1; // eax
  int i; // [rsp+10h] [rbp-10h]
  int j; // [rsp+14h] [rbp-Ch]

  j = 0;
  for ( i = 1; i <= strlen(str1); ++i )
  {
    if ( i % 2 )
    {
      v1 = j++;
      func0_str2[v1] = str1[i - 1];
    }
  }
  func0_str2[j] = 0;
  return func0_str2;
}