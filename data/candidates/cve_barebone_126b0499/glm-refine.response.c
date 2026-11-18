define DNS_TYPE_CNAME      5

int __cdecl ares_parse_a_reply(const unsigned char *abuf, int alen, struct hostent **host)
{
  struct hostent *hostent;
  struct in_addr *addrs;
  char **aliases;
  char *rr_data;
  char *rr_name;
  char *hostname;
  const unsigned char *aptr;
  long len;
  int naliases;
  int naddrs;
  int rr_len;
  int rr_class;
  int rr_type;
  int i;
  int status;
  unsigned int ancount;
  unsigned int qdcount;

  *host = NULL;
  if (alen < 12)
    return ARES_EBADRESP;

  // Parse DNS header counts
  qdcount = (abuf[4] << 8) | abuf[5];
  ancount = (abuf[6] << 8) | abuf[7];

  if (qdcount != 1)
    return ARES_EBADRESP;

  aptr = abuf + 12;
  status = ares_expand_name(abuf + 12, abuf, alen, &hostname, &len);
  if (status)
    return status;

  // Bounds check for Question section (QNAME + QTYPE + QCLASS)
  if (&aptr[len + 4] > &abuf[alen])
  {
    free(hostname);
    return ARES_EBADRESP;
  }
  aptr += len + 4;

  addrs = (struct in_addr *)malloc((size_t)ancount * 4);
  if (!addrs)
  {
    free(hostname);
    return ARES_ENOMEM;
  }

  aliases = (char **)malloc((size_t)(ancount + 1) * sizeof(char *));
  if (!aliases)
  {
    free(hostname);
    free(addrs);
    return ARES_ENOMEM;
  }

  naddrs = 0;
  naliases = 0;

  for (i = 0; i < (int)ancount; ++i)
  {
    status = ares_expand_name(aptr, abuf, alen, &rr_name, &len);
    if (status)
      break;

    aptr += len;

    // Bounds check for Resource Record fixed fields (10 bytes)
    if (aptr + 10 > &abuf[alen])
    {
      free(rr_name);
      status = ARES_EBADRESP;
      break;
    }

    rr_type   = (aptr[0] << 8) | aptr[1];
    rr_class  = (aptr[2] << 8) | aptr[3];
    rr_len    = (aptr[8] << 8) | aptr[9];
    aptr += 10;

    if (rr_class == DNS_CLASS_IN && rr_type == DNS_TYPE_A && rr_len == 4 && !strcasecmp(rr_name, hostname))
    {
      addrs[naddrs++] = *(struct in_addr *)aptr;
      status = ARES_SUCCESS;
    }

    if (rr_class == DNS_CLASS_IN && rr_type == DNS_TYPE_CNAME)
    {
      aliases[naliases++] = rr_name;
      status = ares_expand_name(aptr, abuf, alen, &rr_data, &len);
      if (status)
        break;

      free(hostname);
      hostname = rr_data;
    }
    else
    {
      free(rr_name);
    }

    aptr += rr_len;
    if (aptr > &abuf[alen])
    {
      status = ARES_EBADRESP;
      break;
    }
  }

  if (!status)
    status = (naddrs == 0) ? ARES_ENODATA : ARES_SUCCESS;

  if (!status)
  {
    aliases[naliases] = NULL;
    hostent = (struct hostent *)malloc(0x20uLL);
    if (hostent)
    {
      hostent->h_addr_list = (char **)malloc((size_t)(naddrs + 1) * sizeof(char *));
      if (hostent->h_addr_list)
      {
        hostent->h_name = hostname;
        hostent->h_aliases = aliases;
        hostent->h_addrtype = AF_INET;   // 2
        hostent->h_length = 4;
        
        for (i = 0; i < naddrs; ++i)
          hostent->h_addr_list[i] = (char *)&addrs[i];
          
        hostent->h_addr_list[naddrs] = NULL;
        *host = hostent;
        return ARES_SUCCESS;
      }
      free(hostent);
    }
    status = ARES_ENOMEM;
  }

  // Cleanup path on failure
  for (i = 0; i < naliases; ++i)
    free(aliases[i]);
    
  free(aliases);
  free(addrs);
  free(hostname);
  
  return status;
}