int ares_parse_a_reply(const unsigned char *abuf, int alen,
                       struct hostent **answer) {
  const unsigned char *p;
  char *canonname;
  char **aliases;
  struct in_addr *addr_list;
  int cname_len;
  int addr_count;
  int opcode;
  int rcode;
  int rdlength;
  int rtype;
  int i;
  int status;
  char *cname;
  char *new_canonname;
  struct hostent *host;
  *answer = NULL;
  if (alen < 12) {
    return 10;
  }
  opcode = (abuf[4] << 8) | abuf[5];
  rcode = (abuf[6] << 8) | abuf[7];
  if (opcode != 1) {
    return 10;
  }
  p = abuf + 12;
  status = ares_expand_name(p, abuf, alen, &canonname, &cname_len);
  if (status != 0) {
    return status;
  }
  if (p + 4 + cname_len > abuf + alen) {
    free(canonname);
    return 10;
  }
  p += 4 + cname_len;
  addr_list = malloc(rcode * sizeof(struct in_addr));
  if (addr_list == NULL) {
    free(canonname);
    return 15;
  }
  aliases = malloc((rcode + 1) * sizeof(char *));
  if (aliases == NULL) {
    free(canonname);
    free(addr_list);
    return 15;
  }
  addr_count = 0;
  rdlength = 0;
  for (i = 0; i < rcode; i++) {
    status = ares_expand_name(p, abuf, alen, &cname, &cname_len);
    if (status != 0) {
      break;
    }
    p += cname_len;
    if (p + 10 > abuf + alen) {
      free(cname);
      status = 10;
      break;
    }
    rtype = (p[0] << 8) | p[1];
    status = (p[2] << 8) | p[3];
    rdlength = (p[8] << 8) | p[9];
    p += 10;
    if (status == 1 && rtype == 1 && rdlength == 4 &&
        !strcasecmp(cname, canonname)) {
      addr_list[addr_count] = *(struct in_addr *)p;
      addr_count++;
      status = 0;
    }
    if (status == 1 && rtype == 5) {
      aliases[rdlength] = cname;
      rdlength++;
      status = ares_expand_name(p, abuf, alen, &new_canonname, &cname_len);
      if (status != 0) {
        break;
      }
      free(canonname);
      canonname = new_canonname;
    } else {
      free(cname);
    }
    p += rdlength;
    if (p > abuf + alen) {
      status = 10;
      break;
    }
  }
  if (status == 0) {
    status = (addr_count == 0);
  }
  if (status == 0) {
    aliases[rdlength] = NULL;
    host = malloc(sizeof(struct hostent));
    if (host == NULL) {
      status = 15;
      goto cleanup;
    }
    host->h_addr_list = malloc((addr_count + 1) * sizeof(char *));
    if (host->h_addr_list == NULL) {
      free(host);
      status = 15;
      goto cleanup;
    }
    host->h_name = canonname;
    host->h_aliases = aliases;
    host->h_addrtype = 2;
    host->h_length = 4;
    for (i = 0; i < addr_count; i++) {
      host->h_addr_list[i] = (char *)&addr_list[i];
    }
    host->h_addr_list[addr_count] = NULL;
    *answer = host;
    return 0;
  }
cleanup:
  for (i = 0; i < rdlength; i++) {
    free(aliases[i]);
  }
  free(aliases);
  free(addr_list);
  free(canonname);
  return status;
}