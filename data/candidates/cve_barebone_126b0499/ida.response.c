int __cdecl ares_parse_a_reply(const unsigned __int8 *abuf, int alen, hostent **host)
{
  hostent *hostent; // [rsp+8h] [rbp-88h]
  in_addr *addrs; // [rsp+10h] [rbp-80h]
  char **aliases; // [rsp+18h] [rbp-78h]
  char *rr_data; // [rsp+20h] [rbp-70h] BYREF
  char *rr_name; // [rsp+28h] [rbp-68h] BYREF
  char *hostname; // [rsp+30h] [rbp-60h] BYREF
  const unsigned __int8 *aptr; // [rsp+38h] [rbp-58h]
  int naliases; // [rsp+44h] [rbp-4Ch]
  long len; // [rsp+48h] [rbp-48h] BYREF
  int naddrs; // [rsp+50h] [rbp-40h]
  int rr_len; // [rsp+54h] [rbp-3Ch]
  int rr_class; // [rsp+58h] [rbp-38h]
  int rr_type; // [rsp+5Ch] [rbp-34h]
  int i; // [rsp+60h] [rbp-30h]
  int status; // [rsp+64h] [rbp-2Ch]
  unsigned int ancount; // [rsp+68h] [rbp-28h]
  unsigned int qdcount; // [rsp+6Ch] [rbp-24h]
  hostent **hosta; // [rsp+70h] [rbp-20h]
  int alena; // [rsp+7Ch] [rbp-14h]
  const unsigned __int8 *abufa; // [rsp+80h] [rbp-10h]

  abufa = abuf;
  alena = alen;
  hosta = host;
  *host = 0LL;
  if ( alena < 12 )
    return 10;
  qdcount = abufa[5] | (abufa[4] << 8);
  ancount = abufa[7] | (abufa[6] << 8);
  if ( qdcount != 1 )
    return 10;
  aptr = abufa + 12;
  status = ares_expand_name(abufa + 12, abufa, alena, &hostname, &len);
  if ( status )
    return status;
  if ( &aptr[len + 4] > &abufa[alena] )
  {
    free(hostname);
    return 10;
  }
  aptr += len + 4;
  addrs = (in_addr *)malloc(4LL * ancount);
  if ( !addrs )
  {
    free(hostname);
    return 15;
  }
  aliases = (char **)malloc(8LL * (ancount + 1));
  if ( !aliases )
  {
    free(hostname);
    free(addrs);
    return 15;
  }
  naddrs = 0;
  naliases = 0;
  for ( i = 0; i < (int)ancount; ++i )
  {
    status = ares_expand_name(aptr, abufa, alena, &rr_name, &len);
    if ( status )
      break;
    aptr += len;
    if ( aptr + 10 > &abufa[alena] )
    {
      free(rr_name);
      status = 10;
      break;
    }
    rr_type = aptr[1] | (*aptr << 8);
    rr_class = aptr[3] | (aptr[2] << 8);
    rr_len = aptr[9] | (aptr[8] << 8);
    aptr += 10;
    if ( rr_class == 1 && rr_type == 1 && rr_len == 4LL && !strcasecmp(rr_name, hostname) )
    {
      addrs[naddrs++] = *(in_addr *)aptr;
      status = 0;
    }
    if ( rr_class == 1 && rr_type == 5 )
    {
      aliases[naliases++] = rr_name;
      status = ares_expand_name(aptr, abufa, alena, &rr_data, &len);
      if ( status )
        break;
      free(hostname);
      hostname = rr_data;
    }
    else
    {
      free(rr_name);
    }
    aptr += rr_len;
    if ( aptr > &abufa[alena] )
    {
      status = 10;
      break;
    }
  }
  if ( !status )
    status = naddrs == 0;
  if ( !status )
  {
    aliases[naliases] = 0LL;
    hostent = (hostent *)malloc(0x20uLL);
    if ( hostent )
    {
      hostent->h_addr_list = (char **)malloc(8LL * (naddrs + 1));
      if ( hostent->h_addr_list )
      {
        hostent->h_name = hostname;
        hostent->h_aliases = aliases;
        hostent->h_addrtype = 2;
        hostent->h_length = 4;
        for ( i = 0; i < naddrs; ++i )
          hostent->h_addr_list[i] = (char *)&addrs[i];
        hostent->h_addr_list[naddrs] = 0LL;
        *hosta = hostent;
        return 0;
      }
      free(hostent);
    }
    status = 15;
  }
  for ( i = 0; i < naliases; ++i )
    free(aliases[i]);
  free(aliases);
  free(addrs);
  free(hostname);
  return status;
}