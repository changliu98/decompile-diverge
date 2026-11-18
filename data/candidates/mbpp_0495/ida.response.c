char *__cdecl func0(const char *str1)
{
  int v1; // eax
  int j; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  j = 0;
  for ( i = 0; str1[i]; ++i )
  {
    if ( str1[i] < 97 || str1[i] > 122 )
    {
      v1 = j++;
      func0_result[v1] = str1[i];
    }
  }
  func0_result[j] = 0;
  return func0_result;
}