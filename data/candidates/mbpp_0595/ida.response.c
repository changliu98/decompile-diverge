int __cdecl func0(const char *str1, const char *str2)
{
  int i; // [rsp+Ch] [rbp-24h]
  int len; // [rsp+10h] [rbp-20h]
  int count; // [rsp+14h] [rbp-1Ch]

  count = 0;
  len = strlen(str1);
  for ( i = 0; i < len; ++i )
  {
    if ( str1[i] != str2[i] )
      ++count;
  }
  if ( count % 2 )
    return -1;
  else
    return count / 2;
}