int __cdecl sock_initaddress(
        const char *host,
        const char *port,
        addrinfo *hints,
        addrinfo **addrinfo,
        char *errbuf,
        int errbuflen)
{
  int gai_retval;
  
  // Resolve the address using the provided port, or "0" if port is NULL
  gai_retval = getaddrinfo(host, port ? port : "0", hints, addrinfo);
  
  // Handle getaddrinfo failure
  if (gai_retval != 0) 
  {
    if (errbuf) 
    {
      if (host && port) 
      {
        // Attempt to isolate whether the host or port caused the failure
        if (getaddrinfo(host, NULL, hints, addrinfo) != 0) 
        {
          // Host resolution failed
          get_gai_errstring(errbuf, errbuflen, "", gai_retval, host, NULL);
        } 
        else 
        {
          // Host resolution succeeded, so the port must be invalid
          freeaddrinfo(*addrinfo);
          get_gai_errstring(errbuf, errbuflen, "", gai_retval, NULL, port);
        }
      } 
      else 
      {
        // Either host or port was originally NULL
        get_gai_errstring(errbuf, errbuflen, "", gai_retval, host, port);
      }
    }
    return -1;
  }
  
  // Handle getaddrinfo success: validate the returned address info
  if (IS_SUPPORTED_FAMILY((*addrinfo)->ai_family)) 
  {
    // Check if it's a valid non-multicast TCP address, or a valid UDP address
    if ((*addrinfo)->ai_socktype != SOCK_STREAM || !sock_ismcastaddr((*addrinfo)->ai_addr))
    {
      return 0; // Success
    }
    
    // It's a TCP stream but the address is multicast
    if (errbuf)
      snprintf(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
  } 
  else if (errbuf) 
  {
    // Unsupported address family
    snprintf(errbuf, errbuflen, "getaddrinfo(): socket type not supported");
  }
  
  // Validation failed: clean up and return error
  freeaddrinfo(*addrinfo);
  *addrinfo = NULL;
  return -1;
}