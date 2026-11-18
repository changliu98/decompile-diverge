int __cdecl sock_initaddress(
        const char *host,
        const char *port,
        addrinfo *hints,
        addrinfo **addrinfo,
        char *errbuf,
        int errbuflen)
{
  int v6; // eax
  int retval; // [rsp+18h] [rbp-38h]

  if ( port )
    v6 = getaddrinfo(host, port, hints, addrinfo);
  else
    v6 = getaddrinfo(host, "0", hints, addrinfo);
  retval = v6;
  if ( v6 )
  {
    if ( errbuf )
    {
      if ( host && port )
      {
        if ( getaddrinfo(host, 0LL, hints, addrinfo) )
        {
          get_gai_errstring(errbuf, errbuflen, "", retval, host, 0LL);
        }
        else
        {
          freeaddrinfo(*addrinfo);
          get_gai_errstring(errbuf, errbuflen, "", retval, 0LL, port);
        }
      }
      else
      {
        get_gai_errstring(errbuf, errbuflen, "", v6, host, port);
      }
    }
    return -1;
  }
  else
  {
    if ( (*addrinfo)->ai_family == 2 || (*addrinfo)->ai_family == 10 )
    {
      if ( (*addrinfo)->ai_socktype != 1 || sock_ismcastaddr((*addrinfo)->ai_addr) )
        return 0;
      if ( errbuf )
        snprintf(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
    }
    else if ( errbuf )
    {
      snprintf(errbuf, errbuflen, "getaddrinfo(): socket type not supported");
    }
    freeaddrinfo(*addrinfo);
    *addrinfo = 0LL;
    return -1;
  }
}