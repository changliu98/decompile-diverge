int sock_initaddress(const char *host, const char *service,
                     struct addrinfo *hints, struct addrinfo **res,
                     char *errstring, int errstring_len) {
  int err;
  if (service == NULL)
    err = getaddrinfo(host, "0", hints, res);
  else
    err = getaddrinfo(host, service, hints, res);
  if (err != 0) {
    if (errstring != NULL) {
      if (host == NULL || service == NULL)
        get_gai_errstring(errstring, errstring_len, "", err, host, service);
      else {
        if (getaddrinfo(host, NULL, hints, res) == 0) {
          freeaddrinfo(*res);
          get_gai_errstring(errstring, errstring_len, "", err, NULL, service);
        } else
          get_gai_errstring(errstring, errstring_len, "", err, host, NULL);
      }
    }
    return -1;
  }
  if ((*res)->ai_family != 2 && (*res)->ai_family != 10) {
    if (errstring != NULL)
      snprintf(errstring, errstring_len,
               "getaddrinfo(): socket type not supported");
    freeaddrinfo(*res);
    *res = NULL;
    return -1;
  }
  if ((*res)->ai_socktype == 1 && sock_ismcastaddr((*res)->ai_addr) == 0) {
    if (errstring != NULL)
      snprintf(errstring, errstring_len,
               "getaddrinfo(): multicast addresses are not valid when using "
               "TCP streams");
    freeaddrinfo(*res);
    *res = NULL;
    return -1;
  }
  return 0;
}