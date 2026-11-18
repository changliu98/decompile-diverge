char *__cdecl func0(const char *text1)
{
  size_t v1; // rcx
  size_t v2; // rcx
  int space_found; // [rsp+Ch] [rbp-34h]
  size_t j; // [rsp+10h] [rbp-30h]
  size_t i; // [rsp+18h] [rbp-28h]
  char *result; // [rsp+20h] [rbp-20h]
  size_t len; // [rsp+28h] [rbp-18h]

  if ( !text1 )
    return 0LL;
  len = strlen(text1);
  result = (char *)malloc(len + 1);
  if ( !result )
    return 0LL;
  i = 0LL;
  j = 0LL;
  space_found = 0;
  while ( text1[i] )
  {
    if ( text1[i] == 32 )
    {
      if ( !space_found )
      {
        v2 = j++;
        result[v2] = 32;
        space_found = 1;
      }
    }
    else
    {
      v1 = j++;
      result[v1] = text1[i];
      space_found = 0;
    }
    ++i;
  }
  result[j] = 0;
  return result;
}