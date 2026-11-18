struct address *new_address(char *hostname_or_ip)
{
  struct address *addr;
  char ip_buf[256];
  char *port;
  unsigned long len;
  unsigned int port_num;
  struct sockaddr_storage sa;
  if (!hostname_or_ip)
    return ((void *)0);
  memset(&sa, 0, sizeof(sa));
  if (inet_pton(10, hostname_or_ip, &((struct sockaddr_in6 *)&sa)->sin6_addr.__in6_u.__u6_addr8) == 1) {
    ((struct sockaddr *)&sa)->sa_family = 10;
    return new_address_sa((struct sockaddr *)&sa, sizeof(struct sockaddr_in6));
  }
  memset(&sa, 0, sizeof(sa));
  if (strncmp("unix:", hostname_or_ip, 5) == 0) {
    if (strlen(&hostname_or_ip[5]) >= sizeof(((struct sockaddr_un *)&sa)->sun_path))
      return ((void *)0);
    ((struct sockaddr *)&sa)->sa_family = 1;
    strncpy(((struct sockaddr_un *)&sa)->sun_path, &hostname_or_ip[5], sizeof(((struct sockaddr_un *)&sa)->sun_path)-1);
    return new_address_sa((struct sockaddr *)&sa, sizeof(struct sockaddr_un));
  }
  port = strrchr(hostname_or_ip, ':');
  if (port && is_numeric(port + 1) &&
      ((len = port - hostname_or_ip), (port_num = atoi(port + 1)) <= 0xFFFF) &&
      len < sizeof(ip_buf)) {
    strncpy(ip_buf, hostname_or_ip, len);
    ip_buf[len] = '\0';
    addr = new_address(ip_buf);
    if (addr)
      address_set_port(addr, port_num);
    return addr;
  }
  if (strcmp("*", hostname_or_ip) == 0) {
    addr = (struct address *)malloc(sizeof(struct address));
    if (addr) {
      addr->type = 2;
      addr->len = 0;
      address_set_port(addr, 0);
    }
    return addr;
  }
  memset(&sa, 0, sizeof(sa));
  if (inet_pton(2, hostname_or_ip, &((struct sockaddr_in *)&sa)->sin_addr.__u_addr.__v4_addr) == 1) {
    ((struct sockaddr *)&sa)->sa_family = 2;
    return new_address_sa((struct sockaddr *)&sa, sizeof(struct sockaddr_in));
  }
  memset(&sa, 0, sizeof(sa));
  if (hostname_or_ip[0] == '[' &&
      (port = strchr(hostname_or_ip, ']')) != ((void *)0)) {
    len = port - hostname_or_ip - 1;
    strncpy(ip_buf, hostname_or_ip + 1, len);
    ip_buf[len] = '\0';
    if (inet_pton(10, ip_buf, &((struct sockaddr_in6 *)&sa)->sin6_addr.__in6_u.__u6_addr8) == 1) {
      ((struct sockaddr *)&sa)->sa_family = 10;
      return new_address_sa((struct sockaddr *)&sa, sizeof(struct sockaddr_in6));
    }
  }
  if (valid_hostname(hostname_or_ip)) {
    len = strlen(hostname_or_ip);
    addr = (struct address *)malloc(sizeof(struct address) + len);
    if (addr) {
      addr->type = 0;
      addr->port = 0;
      addr->len = len;
      memcpy(&addr->port + 1, hostname_or_ip, len);
      addr->port[addr->len + 2] = '\0';
      for (port = &addr->port[1]; *port; port++)
        *port = tolower(*port);
    }
    return addr;
  }
  return ((void *)0);
}