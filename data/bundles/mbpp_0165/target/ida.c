int __cdecl func0(const char *str1)
{
  int i; // [rsp+Ch] [rbp-14h]
  int length; // [rsp+10h] [rbp-10h]
  int count_chars; // [rsp+14h] [rbp-Ch]

  count_chars = 0;
  length = strlen(str1);
  for ( i = 0; i < length; ++i )
  {
    if ( i == str1[i] - 65 || i == str1[i] - 97 )
      ++count_chars;
  }
  return count_chars;
}