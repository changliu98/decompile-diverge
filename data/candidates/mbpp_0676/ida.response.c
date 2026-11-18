char *__cdecl func0(const char *text1)
{
  size_t v1; // rcx
  size_t i; // [rsp+0h] [rbp-30h]
  size_t j; // [rsp+8h] [rbp-28h]
  char *result; // [rsp+10h] [rbp-20h]
  size_t len; // [rsp+18h] [rbp-18h]

  len = strlen(text1);
  result = (char *)malloc(len + 1);
  if ( !result )
    return 0LL;
  j = 0LL;
  for ( i = 0LL; i < len; ++i )
  {
    if ( ((*__ctype_b_loc())[(unsigned __int8)text1[i]] & 8) != 0 )
    {
      v1 = j++;
      result[v1] = text1[i];
    }
  }
  result[j] = 0;
  return result;
}