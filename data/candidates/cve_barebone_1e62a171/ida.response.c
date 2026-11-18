int __cdecl name_len(netdissect_options *ndo, const unsigned __int8 *s, const unsigned __int8 *maxbuf)
{
  const unsigned __int8 *sa; // [rsp+12h] [rbp-18h]

  sa = s;
  if ( s >= maxbuf )
    return -1;
  if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || s > ndo->ndo_snapend - 1 )
    return -1;
  if ( (*s & 0xC0) == 192 )
    return 2;
  while ( *sa )
  {
    if ( sa >= maxbuf )
      return -1;
    if ( ndo->ndo_snapend - 1 > ndo->ndo_snapend || sa > ndo->ndo_snapend - 1 )
      return -1;
    sa += *sa + 1;
  }
  return (_DWORD)sa - (_DWORD)s + 1;
}