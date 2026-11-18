int __cdecl anetSockName(int fd, char *ip_0, size_t ip_len, int *port)
{
  socklen_t salen; // [rsp+1Ch] [rbp-A4h] BYREF
  sockaddr_storage sa; // [rsp+20h] [rbp-A0h] BYREF
  int *porta; // [rsp+A0h] [rbp-20h]
  size_t ip_lena; // [rsp+A8h] [rbp-18h]
  char *ip_0a; // [rsp+B0h] [rbp-10h]
  int fda; // [rsp+B8h] [rbp-8h]

  fda = fd;
  ip_0a = ip_0;
  ip_lena = ip_len;
  porta = port;
  salen = 128;
  if ( getsockname(fd, (struct sockaddr *)&sa, &salen) == -1 )
  {
    if ( porta )
      *porta = 0;
    *ip_0a = 63;
    ip_0a[1] = 0;
    return -1;
  }
  else
  {
    if ( sa.ss_family == 2 )
    {
      if ( ip_0a )
        inet_ntop(2, &sa.__ss_padding[2], ip_0a, ip_lena);
      if ( porta )
        *porta = ntohs(*(uint16_t *)sa.__ss_padding);
    }
    else
    {
      if ( ip_0a )
        inet_ntop(10, &sa.__ss_padding[6], ip_0a, ip_lena);
      if ( porta )
        *porta = ntohs(*(uint16_t *)sa.__ss_padding);
    }
    return 0;
  }
}