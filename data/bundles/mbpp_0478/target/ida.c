char *__cdecl func0(char *str1)
{
  int v1; // eax
  int j; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  j = 0;
  for ( i = 0; str1[i]; ++i )
  {
    if ( ((*__ctype_b_loc())[str1[i]] & 0x200) == 0 )
    {
      v1 = j++;
      func0_result[v1] = str1[i];
    }
  }
  func0_result[j] = 0;
  return func0_result;
}