int anetSockName(int fd, char *ip, unsigned long ip_len, int *port)
{
  struct sockaddr_storage sa;
  unsigned int salen = sizeof(sa);
  if (getsockname(fd, (struct sockaddr *)&sa, &salen) == -1) {
    if (port != ((void *)0))
      *port = 0;
    ip[0] = '?';
    ip[1] = '\0';
    return -1;
  }
  if (sa.ss_family == 2) {
    if (ip != ((void *)0))
      inet_ntop(2, &((struct sockaddr_in *)&sa)->sin_addr, ip, ip_len);
    if (port != ((void *)0))
      *port = ntohs(((struct sockaddr_in *)&sa)->sin_port);
  }
  else {
    if (ip != ((void *)0))
      inet_ntop(10, &((struct sockaddr_in6 *)&sa)->sin6_addr, ip, ip_len);
    if (port != ((void *)0))
      *port = ntohs(((struct sockaddr_in6 *)&sa)->sin6_port);
  }
  return 0;
}