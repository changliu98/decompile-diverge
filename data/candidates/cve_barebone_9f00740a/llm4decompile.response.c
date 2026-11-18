void get_conn_text (conn *c, int af, char *addr, void *sockaddr) {
  char addr_text[4096];
  char *proto = "?";
  unsigned short port = 0;
  addr_text[0] = 0;

  if (af == 1) {
    struct sockaddr_un *sa = (struct sockaddr_un *) sockaddr;
    strncpy (addr_text, sa->sun_path, 4096 -1);
    addr_text[4096 -1] = 0;
    proto = "unix";
  } else if (af == 2) {
    struct sockaddr_in *sa = (struct sockaddr_in *) sockaddr;
    inet_ntop (2, &sa->sin_addr, addr_text, 4096 -1);
    port = ntohs (sa->sin_port);
    proto = c->transport == udp_transport ? "udp" : "tcp";
  } else if (af == 10) {
    struct sockaddr_in6 *sa = (struct sockaddr_in6 *) sockaddr;
    addr_text[0] = '[';
    addr_text[1] = 0;
    if (inet_ntop (10, &sa->sin6_addr, addr_text + 1, 4096 -2))
      strcat (addr_text, "]");
    port = ntohs (sa->sin6_port);
    proto = c->transport == udp_transport ? "udp6" : "tcp6";
  }

  if (strlen (addr_text) < 2)
    sprintf (addr_text, "<AF %d>", af);

  if (port)
    sprintf (addr, "%s:%s:%u", proto, addr_text, port);
  else
    sprintf (addr, "%s:%s", proto, addr_text);
}