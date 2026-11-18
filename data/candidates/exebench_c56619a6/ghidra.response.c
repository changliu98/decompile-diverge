int anetSockName(int fd,char *ip,size_t ip_len,int *port)

{
  uint16_t uVar1;
  int iVar2;
  sockaddr_in6 *s_1;
  sockaddr_in *s;
  socklen_t salen;
  sockaddr_storage sa;
  int *port_local;
  size_t ip_len_local;
  char *ip_local;
  int fd_local;
  int local_c;
  
  salen = 0x80;
  iVar2 = getsockname(fd,(sockaddr *)&sa,&salen);
  if (iVar2 == -1) {
    if (port != (int *)0x0) {
      *port = 0;
    }
    *ip = '?';
    ip[1] = '\0';
    local_c = -1;
  }
  else {
    if (sa.ss_family == 2) {
      if (ip != (char *)0x0) {
        inet_ntop(2,sa.__ss_padding + 2,ip,(socklen_t)ip_len);
      }
      if (port != (int *)0x0) {
        uVar1 = ntohs(sa.__ss_padding._0_2_);
        *port = (uint)uVar1;
      }
    }
    else {
      if (ip != (char *)0x0) {
        inet_ntop(10,sa.__ss_padding + 6,ip,(socklen_t)ip_len);
      }
      if (port != (int *)0x0) {
        uVar1 = ntohs(sa.__ss_padding._0_2_);
        *port = (uint)uVar1;
      }
    }
    local_c = 0;
  }
  return local_c;
}