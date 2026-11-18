void inc_ip(unsigned int *ip)
{
  int i;
  for (i = 3; i >= 0; i--) {
    unsigned int x = ntohl(ip[i]) + 1;
    ip[i] = htonl(x);
    if (x != 0)
      break;
  }
}