int __cdecl itostr(char *buf, int buflen, int x)
{
  char ch_0; // [rsp+0h] [rbp-2Ah]
  char *beg; // [rsp+2h] [rbp-28h]
  int cnt; // [rsp+Eh] [rbp-1Ch]
  int xa; // [rsp+12h] [rbp-18h]
  int buflena; // [rsp+16h] [rbp-14h]
  char *bufa; // [rsp+1Ah] [rbp-10h]
  char *bufb; // [rsp+1Ah] [rbp-10h]

  bufa = buf;
  buflena = buflen;
  xa = x;
  cnt = 0;
  if ( buflen <= 0 )
    return 0;
  if ( x < 0 )
  {
    *buf = 45;
    bufa = buf + 1;
    buflena = buflen - 1;
    cnt = 1;
    xa = -x;
  }
  if ( buflena <= 0 )
    return cnt;
  beg = bufa;
  do
  {
    *bufa++ = xa % 10 + 48;
    ++cnt;
    if ( --buflena <= 0 )
      return cnt;
    xa /= 10;
  }
  while ( xa > 0 );
  *bufa = 0;
  for ( bufb = bufa - 1; beg < bufb; --bufb )
  {
    ch_0 = *beg;
    *beg = *bufb;
    *bufb = ch_0;
    ++beg;
  }
  return cnt;
}