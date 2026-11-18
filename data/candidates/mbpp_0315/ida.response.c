char *__cdecl func0(const char *str)
{
  int st; // [rsp+Ch] [rbp-24h]
  int maxlen; // [rsp+10h] [rbp-20h]
  int currlen; // [rsp+14h] [rbp-1Ch]
  int i; // [rsp+18h] [rbp-18h]
  int n; // [rsp+1Ch] [rbp-14h]

  n = strlen(str);
  i = 0;
  currlen = 0;
  maxlen = 0;
  st = -1;
  while ( i < n )
  {
    if ( str[i] == 32 )
    {
      if ( !(currlen % 2) && maxlen < currlen )
      {
        maxlen = currlen;
        st = i - currlen;
      }
      currlen = 0;
    }
    else
    {
      ++currlen;
    }
    ++i;
  }
  if ( !(currlen % 2) && maxlen < currlen )
  {
    maxlen = currlen;
    st = i - currlen;
  }
  if ( st == -1 )
    return (char *)&unk_2004;
  strncpy(func0_result, &str[st], maxlen);
  func0_result[maxlen] = 0;
  return func0_result;
}