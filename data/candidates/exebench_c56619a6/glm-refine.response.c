int __cdecl anetSockName(int fd, char *ip, size_t ip_len, int *port)
{
  socklen_t salen = sizeof(sockaddr_storage);
  sockaddr_storage sa;

  if (getsockname(fd, (struct sockaddr *)&sa, &salen) == -1)
  {
    if (port)
      *port = 0;
    if (ip)
    {
      ip[0] = '?';  // 63
      ip[1] = '\0';
    }
    return -1;
  }

  if (sa.ss_family == AF_INET) // 2
  {
    if (ip)
      inet_ntop(AF_INET, &((sockaddr_in *)&sa)->sin_addr, ip, ip_len);
    if (port)
      *port = ntohs(((sockaddr_in *)&sa)->sin_port);
  }
  else // AF_INET6 (10)
  {
    if (ip)
      inet_ntop(AF_INET6, &((sockaddr_in6 *)&sa)->sin6_addr, ip, ip_len);
    if (port)
      *port = ntohs(((sockaddr_in6 *)&sa)->sin6_port);
  }

  return 0;
}