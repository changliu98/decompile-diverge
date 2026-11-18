void __cdecl reverse(char *str)
{
  char tmp; // [rsp+1h] [rbp-21h]
  size_t j; // [rsp+2h] [rbp-20h]
  size_t i; // [rsp+Ah] [rbp-18h]
  size_t str_len; // [rsp+12h] [rbp-10h]

  for ( str_len = 0LL; str[str_len]; ++str_len )
    ;
  if ( str_len )
  {
    i = 0LL;
    for ( j = str_len - 1; i < j; --j )
    {
      tmp = str[i];
      str[i] = str[j];
      str[j] = tmp;
      ++i;
    }
  }
}