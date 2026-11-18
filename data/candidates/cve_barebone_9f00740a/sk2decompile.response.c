void get_conn_text(struct sockaddr *sa, int af, char *buf,
                   struct sockaddr_storage *ss) {
  char addr[4096];
  char *proto;
  unsigned short port;
  addr[0] = '\0';
  proto = "?";
  port = 0;
  switch (af) {
    case 1:
      strncpy(addr, ss->sa_data, 4096 - 1);
      addr[4096 - 1] = '\0';
      proto = "unix";
      break;
    case 2:
      inet_ntop(af, &((struct sockaddr_in *)ss)->sin_addr, addr, 4096 - 1);
      port = ntohs(((struct sockaddr_in *)ss)->sin_port);
      proto = (sa->sa_family == AF_INET) ? "udp" : "tcp";
      break;
    case 10:
      strcpy(addr, "[");
      if (inet_ntop(af, &((struct sockaddr_in6 *)ss)->sin6_addr, addr + 1,
                    4096 - 2))
        strcat(addr, "]");
      port = ntohs(((struct sockaddr_in6 *)ss)->sin6_port);
      proto = (sa->sa_family == AF_INET) ? "udp6" : "tcp6";
      break;
  }
  if (strlen(addr) < 2) sprintf(addr, "<AF %d>", af);
  if (port)
    sprintf(buf, "%s:%s:%u", proto, addr, port);
  else
    sprintf(buf, "%s:%s", proto, addr);
}