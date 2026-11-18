char *__cdecl func0(const char *str1, char *result)
{
  int v2; // ecx
  int i; // [rsp+8h] [rbp-18h]
  int j; // [rsp+Ch] [rbp-14h]

  j = 0;
  for ( i = 0; i < strlen(str1); ++i )
  {
    if ( ((*__ctype_b_loc())[str1[i]] & 0x2000) == 0 )
    {
      v2 = j++;
      result[v2] = str1[i];
    }
  }
  result[j] = 0;
  return result;
}