char *__cdecl func0(const char *str1)
{
  size_t i; // [rsp+8h] [rbp-28h]
  char *result; // [rsp+10h] [rbp-20h]
  size_t len; // [rsp+18h] [rbp-18h]

  len = strlen(str1);
  result = (char *)malloc(len + 1);
  if ( !result )
    return 0LL;
  if ( len )
  {
    *result = toupper(*str1);
    for ( i = 1LL; i < len; ++i )
      result[i] = tolower(str1[i]);
    result[len - 1] = toupper(result[len - 1]);
    result[len] = 0;
  }
  return result;
}