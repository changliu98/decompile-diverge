int ares_parse_a_reply(unsigned char *abuf, int alen, struct hostent **host)
{
  unsigned char *aptr;
  int qdcount;
  int ancount;
  int i;
  int status;
  int rr_len;
  int rr_class;
  int rr_type;
  int naddrs;
  int naliases;
  int addr_len;
  int rr_dlen;
  char *hostname;
  char *rr_name;
  char *rr_data;
  char **addrs;
  char **aliases;
  struct hostent *result;
  size_t len;

  *host = NULL;


  if (alen < 12)
    return 10;


  qdcount = ((((int)abuf[4]) << 8) | ((int)abuf[5]));
  ancount = ((((int)abuf[6]) << 8) | ((int)abuf[7]));
  if (qdcount != 1)
    return 10;


  aptr = abuf + 12;
  status = ares_expand_name(aptr, abuf, alen, &hostname, &len);
  if (status != 0)
    return status;
  aptr += len + 4;
  if (aptr > abuf + alen)
    {
      free(hostname);
      return 10;
    }


  addrs = malloc(ancount * sizeof(struct in_addr));
  if (!addrs)
    {
      free(hostname);
      return 15;
    }


  aliases = malloc((ancount + 1) * sizeof(char *));
  if (!aliases)
    {
      free(hostname);
      free(addrs);
      return 15;
    }


  naddrs = 0;
  naliases = 0;
  for (i = 0; i < ancount; i++)
    {
      if (aptr > abuf + alen)
        {
          status = 10;
          break;
        }
      status = ares_expand_name(aptr, abuf, alen, &rr_name, &len);
      if (status != 0)
        break;
      aptr += len;
      if (aptr + 10 > abuf + alen)
        {
          free(rr_name);
          status = 10;
          break;
        }
      rr_type = ((((int)aptr[0]) << 8) | ((int)aptr[1]));
      rr_class = ((((int)aptr[2]) << 8) | ((int)aptr[3]));
      rr_dlen = ((((int)aptr[8]) << 8) | ((int)aptr[9]));
      aptr += 10;


      if (rr_class == 1 && rr_type == 1 && rr_dlen == 4 &&
          !strcasecmp(rr_name, hostname))
        {
          addrs[naddrs].s_addr = *(unsigned long *)aptr;
          naddrs++;
          status = 0;
        }


      if (rr_class == 1 && rr_type == 5)
        {
          aliases[naliases++] = rr_name;
          status = ares_expand_name(aptr, abuf, alen, &rr_data, &len);
          if (status != 0)
            break;
          free(hostname);
          hostname = rr_data;
        }
      else
        free(rr_name);

      aptr += rr_dlen;
    }


  if (status == 0 && naddrs == 0)
    status = 1;


  if (status == 0)
    {
      aliases[naliases] = NULL;
      result = malloc(sizeof(struct hostent));
      if (!result)
        status = 15;
      else
        {
          result->h_addr_list = malloc((naddrs + 1) * sizeof(char *));
          if (!result->h_addr_list)
            {
              free(result);
              status = 15;
            }
          else
            {
              result->h_name = hostname;
              result->h_aliases = aliases;
              result->h_addrtype = 2;
              result->h_length = 4;
              for (i = 0; i < naddrs; i++)
                result->h_addr_list[i] = (char *)&addrs[i];
              result->h_addr_list[naddrs] = NULL;
              *host = result;
            }
        }
    }


  if (status != 0)
    {
      for (i = 0; i < naliases; i++)
        free(aliases[i]);
      free(aliases);
      free(addrs);
      free(hostname);
    }

  return status;
}