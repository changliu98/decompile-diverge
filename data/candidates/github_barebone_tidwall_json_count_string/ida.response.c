size_t __cdecl count_string(uint8_t *raw, uint8_t *end, int *infoout)
{
  bool e; // [rsp+1h] [rbp-2Dh]
  int info; // [rsp+2h] [rbp-2Ch]
  size_t i; // [rsp+6h] [rbp-28h]
  size_t len; // [rsp+Eh] [rbp-20h]

  len = end - raw;
  i = 1LL;
  info = 0;
  e = 0;
  while ( i + 8 <= len )
  {
    if ( strtoksa[raw[i]] )
      goto tok;
    e = 0;
    if ( strtoksa[raw[++i]] )
      goto tok;
    e = 0;
    if ( strtoksa[raw[++i]] )
      goto tok;
    e = 0;
    if ( strtoksa[raw[++i]] )
      goto tok;
    e = 0;
    if ( strtoksa[raw[++i]]
      || (e = 0, ++i, strtoksa[raw[i]])
      || (e = 0, ++i, strtoksa[raw[i]])
      || (e = 0, ++i, strtoksa[raw[i]]) )
    {
tok:
      if ( raw[i] == 34 )
      {
        ++i;
        if ( !e )
          goto LABEL_22;
        e = 0;
      }
      else
      {
        if ( raw[i] == 92 )
        {
          info |= 1u;
          e = !e;
        }
        ++i;
      }
    }
    else
    {
      e = 0;
      ++i;
    }
  }
  while ( i + 1 <= len )
  {
    if ( strtoksa[raw[i]] )
      goto tok;
    e = 0;
    ++i;
  }
LABEL_22:
  *infoout = info;
  return i;
}