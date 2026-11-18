int ares_parse_a_reply(unsigned char *abuf, int alen, struct hostent **host)
{
  struct hostent *hostinfo;
  unsigned char *ptr;
  int status, len, ancount, i, rr_type, rr_class, rdlength, naddrs, naliases;
  char *name, *rr_name, *cname, *tmp;
  unsigned long addr;
  char *alias, **aliases, **tmp_aliases;
  struct in_addr *addrs;

  *host = NULL;


  if (alen < 13)
    return 10;

  ancount = (((abuf)[6] << 8) | (abuf)[7]);
  if (ancount != 1)
    {
      return 10;
    }

  ptr = abuf + 12;
  status = ares_expand_name(ptr, abuf, alen, &name, &len);
  if (status != 0)
    return status;
  if (ptr + len + 4 > abuf + alen)
    {
      free(name);
      return 10;
    }
  ptr += len;

  addrs = malloc(sizeof(struct in_addr) * (ancount + 1));
  if (!addrs)
    {
      free(name);
      return 15;
    }
  aliases = malloc((ancount + 1) * sizeof(char *));
  if (!aliases)
    {
      free(name);
      free(addrs);
      return 15;
    }

  naddrs = 0;
  naliases = 0;
  for (i = 0; i < ancount; i++)
    {
      status = ares_expand_name(ptr, abuf, alen, &rr_name, &len);
      if (status != 0)
 break;
      ptr += len;
      if (ptr + 10 > abuf + alen)
 {
   free(rr_name);
   status = 10;
   break;
 }
      rr_type = (((ptr)[0] << 8) | (ptr)[1]);
      rr_class = (((ptr)[2] << 8) | (ptr)[3]);
      rdlength = (((ptr)[8] << 8) | (ptr)[9]);
      ptr += 10;
      if (rr_class == 1)
 {
   if (rr_type == 1 && rdlength == 4 &&
       strcasecmp(rr_name, name) == 0)
     {

       memcpy(&addr, ptr, sizeof(addr));
       addrs[naddrs].s_addr = addr;
       naddrs++;
       status = 0;
     }
   else if (rr_type == 5)
     {

       aliases[naliases] = rr_name;
       naliases++;
       status = ares_expand_name(ptr, abuf, alen, &cname, &len);
       if (status != 0)
  break;
       free(name);
       name = cname;
     }
   else
     {

       free(rr_name);
     }
 }
      else
 {

   free(rr_name);
 }
      ptr += rdlength;
      if (ptr > abuf + alen)
 {
   status = 10;
   break;
 }
    }

  if (status == 0 && naddrs == 0)
    status = 1;

  if (status != 0)
    {
      for (i = 0; i < naliases; i++)
 free(aliases[i]);
      free(aliases);
      free(addrs);
      free(name);
      return status;
    }


  aliases[naliases] = NULL;
  hostinfo = malloc(sizeof(struct hostent));
  if (!hostinfo)
    {
      free(aliases);
      free(addrs);
      free(name);
      return 15;
    }
  hostinfo->h_addr_list = malloc((naddrs + 1) * sizeof(char *));
  if (!hostinfo->h_addr_list)
    {
      free(hostinfo);
      free(aliases);
      free(addrs);
      free(name);
      return 15;
    }
  hostinfo->h_name = name;
  hostinfo->h_aliases = aliases;
  hostinfo->h_addrtype = 2;
  hostinfo->h_length = sizeof(struct in_addr);
  for (i = 0; i < naddrs; i++)
    {
      hostinfo->h_addr_list[i] =
 (char *)&(addrs[i]);
    }
  hostinfo->h_addr_list[naddrs] = NULL;
  *host = hostinfo;
  return 0;
}