void __cdecl get_conn_text(const conn *c, const int af_0, char *addr, sockaddr *sock_addr)
{
  char addr_text[4096] = {0};
  const char *protoname = "?";
  uint16_t port = 0;

  switch (af_0)
  {
    case 1: // AF_UNIX
      strncpy(addr_text, sock_addr->sa_data, 0xFFF);
      addr_text[4095] = 0;
      protoname = "unix";
      break;

    case 2: // AF_INET
      inet_ntop(af_0, &sock_addr->sa_data[2], addr_text, 0xFFF);
      port = ntohs(*(uint16_t *)sock_addr->sa_data);
      protoname = (c->transport == network_transport::udp_transport) ? "udp" : "tcp";
      break;

    case 10: // AF_INET6
      strcpy(addr_text, "[");
      if (inet_ntop(af_0, &sock_addr->sa_data[6], &addr_text[1], 0xFFE))
        strcat(addr_text, "]");
      port = ntohs(*(uint16_t *)sock_addr->sa_data);
      protoname = (c->transport == network_transport::udp_transport) ? "udp6" : "tcp6";
      break;
  }

  if (strlen(addr_text) < 2)
    sprintf(addr_text, "<AF %d>", af_0);

  if (port)
    sprintf(addr, "%s:%s:%u", protoname, addr_text, port);
  else
    sprintf(addr, "%s:%s", protoname, addr_text);
}