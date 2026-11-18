enamemem *__cdecl lookup_bytestring(netdissect_options *ndo, const u_char *bs, const unsigned int nlen)
{
  int k; // [rsp+Ch] [rbp-34h]
  int j; // [rsp+10h] [rbp-30h]
  int i; // [rsp+14h] [rbp-2Ch]
  enamemem *tp; // [rsp+18h] [rbp-28h]

  if ( nlen < 6 )
  {
    if ( nlen < 4 )
    {
      k = 0;
      j = 0;
    }
    else
    {
      k = bs[1] | (*bs << 8);
      j = bs[3] | (bs[2] << 8);
    }
    i = 0;
  }
  else
  {
    k = bs[1] | (*bs << 8);
    j = bs[3] | (bs[2] << 8);
    i = bs[5] | (bs[4] << 8);
  }
  for ( tp = (enamemem *)((char *)&bytestringtable + 32 * (((unsigned __int16)j ^ (unsigned __int16)i) & 0xFFF));
        tp->e_nxt;
        tp = tp->e_nxt )
  {
    if ( tp->e_addr0 == i && tp->e_addr1 == j && tp->e_addr2 == k && !memcmp(bs, tp->e_nsap, nlen) )
      return tp;
  }
  tp->e_addr0 = i;
  tp->e_addr1 = j;
  tp->e_addr2 = k;
  tp->e_nsap = (u_char *)calloc(1uLL, nlen + 1);
  if ( !tp->e_nsap )
    ndo->ndo_error(ndo, "lookup_bytestring: calloc");
  memcpy(tp->e_nsap, bs, nlen);
  tp->e_nxt = (enamemem *)calloc(1uLL, 0x20uLL);
  if ( !tp->e_nxt )
    ndo->ndo_error(ndo, "lookup_bytestring: calloc");
  return tp;
}