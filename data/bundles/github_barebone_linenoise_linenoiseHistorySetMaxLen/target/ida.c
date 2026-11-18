int __cdecl linenoiseHistorySetMaxLen(int len)
{
  int j; // [rsp+8h] [rbp-18h]
  int tocopy; // [rsp+Ch] [rbp-14h]
  char **newa; // [rsp+10h] [rbp-10h]

  if ( len < 1 )
    return 0;
  if ( history )
  {
    tocopy = history_len;
    newa = (char **)malloc(8LL * len);
    if ( !newa )
      return 0;
    if ( len < tocopy )
    {
      for ( j = 0; j < tocopy - len; ++j )
        free(*((void **)history + j));
      tocopy = len;
    }
    memset(newa, 0, 8LL * len);
    memcpy(newa, (char *)history + 8 * (history_len - tocopy), 8LL * tocopy);
    free(history);
    history = newa;
  }
  history_max_len = len;
  if ( history_len > len )
    history_len = history_max_len;
  return 1;
}