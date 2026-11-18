void get_conn_text(conn *c,int af,char *addr,sockaddr *sock_addr)

{
  char *pcVar1;
  size_t sVar2;
  unsigned_short port;
  char *protoname;
  char addr_text [4096];
  sockaddr *sock_addr_local;
  char *addr_local;
  int af_local;
  conn *c_local;
  
  addr_text[0] = '\0';
  protoname = "?";
  port = 0;
  if (af == 1) {
    strncpy(addr_text,sock_addr->sa_data,0xfff);
    addr_text[0xfff] = '\0';
    protoname = "unix";
  }
  else if (af == 2) {
    inet_ntop(2,sock_addr->sa_data + 2,addr_text,0xfff);
    port = ntohs(*(uint16_t *)sock_addr->sa_data);
    protoname = "tcp";
    if (c->transport == udp_transport) {
      protoname = "udp";
    }
  }
  else if (af == 10) {
    addr_text[0] = '[';
    addr_text[1] = '\0';
    pcVar1 = inet_ntop(10,sock_addr->sa_data + 6,addr_text + 1,0xffe);
    if (pcVar1 != (char *)0x0) {
      strcat(addr_text,"]");
    }
    port = ntohs(*(uint16_t *)sock_addr->sa_data);
    protoname = "tcp6";
    if (c->transport == udp_transport) {
      protoname = "udp6";
    }
  }
  sVar2 = strlen(addr_text);
  if (sVar2 < 2) {
    sprintf(addr_text,"<AF %d>",(ulong)(uint)af);
  }
  if (port == 0) {
    sprintf(addr,"%s:%s",protoname,addr_text);
  }
  else {
    sprintf(addr,"%s:%s:%u",protoname,addr_text,(ulong)port);
  }
  return;
}