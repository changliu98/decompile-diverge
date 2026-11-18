int sock_initaddress(char *host,char *port,addrinfo *hints,addrinfo **addrinfo,char *errbuf,
                    int errbuflen)

{
  int iVar1;
  int iVar2;
  char *local_58;
  int try_retval;
  int retval;
  int errbuflen_local;
  char *errbuf_local;
  addrinfo **addrinfo_local;
  addrinfo *hints_local;
  char *port_local;
  char *host_local;
  int local_c;
  
  local_58 = port;
  if (port == (char *)0x0) {
    local_58 = "0";
  }
  iVar1 = getaddrinfo(host,local_58,(addrinfo *)hints,(addrinfo **)addrinfo);
  if (iVar1 == 0) {
    if (((*addrinfo)->ai_family == 2) || ((*addrinfo)->ai_family == 10)) {
      if (((*addrinfo)->ai_socktype == 1) &&
         (iVar1 = sock_ismcastaddr((*addrinfo)->ai_addr), iVar1 == 0)) {
        if (errbuf != (char *)0x0) {
          snprintf(errbuf,(long)errbuflen,
                   "getaddrinfo(): multicast addresses are not valid when using TCP streams");
        }
        freeaddrinfo((addrinfo *)*addrinfo);
        *addrinfo = (addrinfo *)0x0;
        local_c = -1;
      }
      else {
        local_c = 0;
      }
    }
    else {
      if (errbuf != (char *)0x0) {
        snprintf(errbuf,(long)errbuflen,"getaddrinfo(): socket type not supported");
      }
      freeaddrinfo((addrinfo *)*addrinfo);
      *addrinfo = (addrinfo *)0x0;
      local_c = -1;
    }
  }
  else {
    if (errbuf != (char *)0x0) {
      if ((host == (char *)0x0) || (port == (char *)0x0)) {
        get_gai_errstring(errbuf,errbuflen,"",iVar1,host,port);
      }
      else {
        iVar2 = getaddrinfo(host,(char *)0x0,(addrinfo *)hints,(addrinfo **)addrinfo);
        if (iVar2 == 0) {
          freeaddrinfo((addrinfo *)*addrinfo);
          get_gai_errstring(errbuf,errbuflen,"",iVar1,(char *)0x0,port);
        }
        else {
          get_gai_errstring(errbuf,errbuflen,"",iVar1,host,(char *)0x0);
        }
      }
    }
    local_c = -1;
  }
  return local_c;
}