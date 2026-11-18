size_t __cdecl modp_rtrim(char *str, size_t len)
{
  char c; // [rsp+1h] [rbp-11h]

  while ( len )
  {
    c = str[len - 1];
    if ( c != 32 && c != 10 && c != 9 && c != 13 )
      break;
    str[--len] = 0;
  }
  return len;
}