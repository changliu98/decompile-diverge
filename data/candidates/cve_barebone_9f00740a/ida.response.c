void __cdecl get_conn_text(const conn *c, const int af_0, char *addr, sockaddr *sock_addr)
{
  const char *v4; // rax
  const char *v5; // rax
  unsigned __int16 port; // [rsp+6h] [rbp-102Ah]
  const char *protoname; // [rsp+8h] [rbp-1028h]
  char addr_text[4096]; // [rsp+10h] [rbp-1020h] BYREF
  sockaddr *sock_addra; // [rsp+1010h] [rbp-20h]
  char *addra; // [rsp+1018h] [rbp-18h]
  int af_0a; // [rsp+1024h] [rbp-Ch]
  const conn *ca; // [rsp+1028h] [rbp-8h]

  ca = c;
  af_0a = af_0;
  addra = addr;
  sock_addra = sock_addr;
  addr_text[0] = 0;
  protoname = "?";
  port = 0;
  switch ( af_0 )
  {
    case 1:
      strncpy(addr_text, sock_addra->sa_data, 0xFFFuLL);
      addr_text[4095] = 0;
      protoname = "unix";
      break;
    case 2:
      inet_ntop(af_0a, &sock_addra->sa_data[2], addr_text, 0xFFFu);
      port = ntohs(*(_WORD *)sock_addra->sa_data);
      v4 = "tcp";
      if ( ca->transport == network_transport::udp_transport )
        v4 = "udp";
      protoname = v4;
      break;
    case 10:
      strcpy(addr_text, "[");
      if ( inet_ntop(af_0a, &sock_addra->sa_data[6], &addr_text[1], 0xFFEu) )
        strcat(addr_text, "]");
      port = ntohs(*(_WORD *)sock_addra->sa_data);
      v5 = "tcp6";
      if ( ca->transport == network_transport::udp_transport )
        v5 = "udp6";
      protoname = v5;
      break;
  }
  if ( strlen(addr_text) < 2 )
    sprintf(addr_text, "<AF %d>", (unsigned int)af_0a);
  if ( port )
    sprintf(addra, "%s:%s:%u", protoname, addr_text, port);
  else
    sprintf(addra, "%s:%s", protoname, addr_text);
}