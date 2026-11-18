char *__cdecl func0(const char *str)
{
  int is_palindrome; // [rsp+4h] [rbp-2Ch]
  char *result; // [rsp+8h] [rbp-28h]
  int j; // [rsp+14h] [rbp-1Ch]
  int ja; // [rsp+14h] [rbp-1Ch]
  int jb; // [rsp+14h] [rbp-1Ch]
  int i; // [rsp+18h] [rbp-18h]
  int len; // [rsp+1Ch] [rbp-14h]

  len = strlen(str);
  result = (char *)malloc(2 * len + 1);
  if ( !result )
    return 0LL;
  for ( i = 0; i < len; ++i )
  {
    is_palindrome = 1;
    for ( j = 0; j < (len - i) / 2; ++j )
    {
      if ( str[j + i] != str[len - 1 - j] )
      {
        is_palindrome = 0;
        break;
      }
    }
    if ( is_palindrome )
    {
      strncpy(result, str, len);
      for ( ja = 0; ja < i; ++ja )
        result[ja + len] = str[i - ja - 1];
      result[i + len] = 0;
      return result;
    }
  }
  strncpy(result, str, len);
  for ( jb = 0; jb < len; ++jb )
    result[jb + len] = str[len - jb - 1];
  result[2 * len] = 0;
  return result;
}