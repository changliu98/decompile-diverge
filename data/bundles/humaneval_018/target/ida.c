int __cdecl func0(const char *str, const char *substring)
{
  int i; // [rsp+8h] [rbp-28h]
  int sub_len; // [rsp+Ch] [rbp-24h]
  int str_len; // [rsp+10h] [rbp-20h]
  int out; // [rsp+14h] [rbp-1Ch]

  out = 0;
  str_len = strlen(str);
  sub_len = strlen(substring);
  if ( !str_len )
    return 0;
  for ( i = 0; i <= str_len - sub_len; ++i )
  {
    if ( !strncmp(&str[i], substring, sub_len) )
      ++out;
  }
  return out;
}