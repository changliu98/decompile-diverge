int sock_initaddress(char *host, char *port, struct addrinfo *hints, struct addrinfo **res, char *errbuf, int errbuflen)
{
  int ret;
  if (port)
    ret = get_addrinfo_port(host, port, hints, res);
  else
    ret = get_addrinfo_port(host, "0", hints, res);
  if (ret != 0)
  {
    if (errbuf)
    {
      if (host == ((void *)0) || port == ((void *)0))
        err_getaddrinfo(errbuf, errbuflen, "", ret, host, port);
      else if (get_addrinfo_port(host, ((void *)0), hints, res) != 0)
        err_getaddrinfo(errbuf, errbuflen, "", ret, host, ((void *)0));
      else
      {
        print_addrinfo(*res);
        err_getaddrinfo(errbuf, errbuflen, "", ret, ((void *)0), port);
      }
    }
    return -1;
  }
  if (
    ((*res)->ai_family == 2 || (*res)->ai_family == 10) &&
    ((*res)->ai_socktype == SOCK_STREAM && !is_valid_ip((*res)->ai_addr))
  )
  {
    if (errbuf)
      err_is_valid_ip(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
    print_addrinfo(*res);
    *res = ((void *)0);
    return -1;
  }
  if (errbuf)
  {
    if (
      ((*res)->ai_family == 2 || (*res)->ai_family == 10) &&
      ((*res)->ai_socktype == SOCK_STREAM)
    )
      err_is_valid_ip(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
    else
      err_is_valid_ip(errbuf, errbuflen, "getaddrinfo(): socket type not supported");
  }
  print_addrinfo(*res);
  *res = ((void *)0);
  return -1;
}