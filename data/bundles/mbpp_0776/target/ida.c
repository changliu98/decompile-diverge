int __cdecl func0(const char *test_str)
{
  int idx; // [rsp+0h] [rbp-20h]
  int len; // [rsp+4h] [rbp-1Ch]
  int res; // [rsp+14h] [rbp-Ch]

  res = 0;
  len = strlen(test_str);
  for ( idx = 1; idx < len - 1; ++idx )
  {
    if ( !strchr("aeiou", test_str[idx]) && (strchr("aeiou", test_str[idx - 1]) || strchr("aeiou", test_str[idx + 1])) )
      ++res;
  }
  if ( !strchr("aeiou", *test_str) && strchr("aeiou", test_str[1]) )
    ++res;
  if ( !strchr("aeiou", test_str[len - 1]) && strchr("aeiou", test_str[len - 2]) )
    ++res;
  return res;
}