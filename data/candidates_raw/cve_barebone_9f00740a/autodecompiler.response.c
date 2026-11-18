static int format_address(struct protoent *pe, int af, char *buf, char *addr)
{
 char addrbuf[4096] = "";
 char *proto = "?";
 unsigned short port = 0;
 int i = af;

 switch (i) {
 case 2:
  inet_ntop(af, ((struct sockaddr_in *)addr + 1), addrbuf, sizeof(addrbuf)-1);
  port = ((struct sockaddr_in *)addr)->sin_port;
  proto = pe->p_proto == 2 ? "udp" : "tcp";
  break;
 case 10:
  addrbuf[0] = '[';
  addrbuf[1] = '\0';
  if (inet_ntop(af, ((struct sockaddr_in6 *)addr + 1), addrbuf + 1, sizeof(addrbuf)-2))
   strcat(addrbuf, "]");
  port = ((struct sockaddr_in6 *)addr)->sin6_port;
  proto = pe->p_proto == 2 ? "udp6" : "tcp6";
  break;
 case 1:
  strncpy(addrbuf, ((struct sockaddr_un *)addr + 1), sizeof(addrbuf)-1);
  addrbuf[sizeof(addrbuf)-1] = '\0';
  proto = "unix";
  break;
 default:
  if (strlen(addrbuf) < sizeof(addrbuf) - 2)
   sprintf(addrbuf, "<AF %d>", af);
 }

 if (strlen(addrbuf) < 3)
  sprintf(addrbuf, "<AF %d>", af);

 if (port)
  return sprintf(buf, "%s:%s:%u", proto, addrbuf, port);
 else
  return sprintf(buf, "%s:%s", proto, addrbuf);
}