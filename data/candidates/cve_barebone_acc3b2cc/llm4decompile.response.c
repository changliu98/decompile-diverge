int sock_initaddress(char *host, char *port, struct addrinfo *hints, struct addrinfo **addrinfo, char *errbuf, int errbuflen)
{
 int retval;

 if (port == NULL) {
  port = "0";
 }

 retval = getaddrinfo(host, port, hints, addrinfo);
 if (retval != 0) {
  if (errbuf != NULL) {
   if (host == NULL || port == NULL) {
    get_gai_errstring(errbuf, errbuflen, "", retval, host, port);
   } else {
    int tmp_retval;


    tmp_retval = getaddrinfo(host, NULL, hints, addrinfo);
    if (tmp_retval != 0) {
     get_gai_errstring(errbuf, errbuflen, "", retval, host, NULL);
    } else {
     freeaddrinfo(*addrinfo);
     get_gai_errstring(errbuf, errbuflen, "", retval, NULL, port);
    }
   }
  }
  return -1;
 }

 if ((*addrinfo)->ai_family != 2 && (*addrinfo)->ai_family != 10) {
  if (errbuf != NULL) {
   snprintf(errbuf, errbuflen, "getaddrinfo(): socket type not supported");
  }
  freeaddrinfo(*addrinfo);
  *addrinfo = NULL;
  return -1;
 }

 if ((*addrinfo)->ai_protocol == 1 && !sock_ismcastaddr((*addrinfo)->ai_addr)) {
  if (errbuf != NULL) {
   snprintf(errbuf, errbuflen, "getaddrinfo(): multicast addresses are not valid when using TCP streams");
  }
  freeaddrinfo(*addrinfo);
  *addrinfo = NULL;
  return -1;
 }

 return 0;
}