int ares_parse_a_reply(uchar *abuf,int alen,hostent **host)

{
  int iVar1;
  void *__ptr;
  char **__ptr_00;
  hostent *__ptr_01;
  char **ppcVar2;
  hostent *hostent;
  in_addr *addrs;
  char **aliases;
  char *rr_data;
  char *rr_name;
  char *hostname;
  uchar *aptr;
  int naliases;
  long len;
  int naddrs;
  int rr_len;
  int rr_class;
  int rr_type;
  int i;
  int status;
  uint ancount;
  uint qdcount;
  hostent **host_local;
  int alen_local;
  uchar *abuf_local;
  int local_c;
  
  *host = (hostent *)0x0;
  if (alen < 0xc) {
    local_c = 10;
  }
  else {
    qdcount = (uint)CONCAT11(abuf[4],abuf[5]);
    ancount = (uint)CONCAT11(abuf[6],abuf[7]);
    if (qdcount == 1) {
      aptr = abuf + 0xc;
      host_local = host;
      alen_local = alen;
      abuf_local = abuf;
      status = ares_expand_name(aptr,abuf,alen,&hostname,&len);
      local_c = status;
      if (status == 0) {
        if (abuf_local + alen_local < aptr + len + 4) {
          free(hostname);
          local_c = 10;
        }
        else {
          aptr = aptr + len + 4;
          __ptr = malloc((ulong)ancount << 2);
          if (__ptr == (void *)0x0) {
            free(hostname);
            local_c = 0xf;
          }
          else {
            __ptr_00 = malloc((ulong)(ancount + 1) << 3);
            if (__ptr_00 == (char **)0x0) {
              free(hostname);
              free(__ptr);
              local_c = 0xf;
            }
            else {
              naddrs = 0;
              naliases = 0;
              i = 0;
              while( true ) {
                if (((int)ancount <= i) ||
                   (status = ares_expand_name(aptr,abuf_local,alen_local,&rr_name,&len), status != 0
                   )) goto LAB_00101902;
                aptr = aptr + len;
                if (abuf_local + alen_local < aptr + 10) break;
                rr_type = (int)CONCAT11(*aptr,aptr[1]);
                rr_class = (int)CONCAT11(aptr[2],aptr[3]);
                rr_len = (int)CONCAT11(aptr[8],aptr[9]);
                aptr = aptr + 10;
                if ((((rr_class == 1) && (rr_type == 1)) && (rr_len == 4)) &&
                   (iVar1 = strcasecmp(rr_name,hostname), iVar1 == 0)) {
                  *(undefined4 *)((long)__ptr + (long)naddrs * 4) = *(undefined4 *)aptr;
                  naddrs = naddrs + 1;
                  status = 0;
                }
                if ((rr_class == 1) && (rr_type == 5)) {
                  __ptr_00[naliases] = rr_name;
                  naliases = naliases + 1;
                  status = ares_expand_name(aptr,abuf_local,alen_local,&rr_data,&len);
                  if (status != 0) goto LAB_00101902;
                  free(hostname);
                  hostname = rr_data;
                }
                else {
                  free(rr_name);
                }
                aptr = aptr + rr_len;
                if (abuf_local + alen_local < aptr) {
                  status = 10;
                  goto LAB_00101902;
                }
                i = i + 1;
              }
              free(rr_name);
              status = 10;
LAB_00101902:
              if ((status == 0) && (naddrs == 0)) {
                status = 1;
              }
              if (status == 0) {
                __ptr_00[naliases] = (char *)0x0;
                __ptr_01 = malloc(0x20);
                if (__ptr_01 != (hostent *)0x0) {
                  ppcVar2 = malloc((long)(naddrs + 1) << 3);
                  __ptr_01->h_addr_list = ppcVar2;
                  if (__ptr_01->h_addr_list != (char **)0x0) {
                    __ptr_01->h_name = hostname;
                    __ptr_01->h_aliases = __ptr_00;
                    __ptr_01->h_addrtype = 2;
                    __ptr_01->h_length = 4;
                    for (i = 0; i < naddrs; i = i + 1) {
                      __ptr_01->h_addr_list[i] = (char *)((long)__ptr + (long)i * 4);
                    }
                    __ptr_01->h_addr_list[naddrs] = (char *)0x0;
                    *host_local = __ptr_01;
                    return 0;
                  }
                  free(__ptr_01);
                }
                status = 0xf;
              }
              for (i = 0; i < naliases; i = i + 1) {
                free(__ptr_00[i]);
              }
              free(__ptr_00);
              free(__ptr);
              free(hostname);
              local_c = status;
            }
          }
        }
      }
    }
    else {
      local_c = 10;
    }
  }
  return local_c;
}