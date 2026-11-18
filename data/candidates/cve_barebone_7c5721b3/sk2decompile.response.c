Address *new_address(const char *str) {
  char buf[262];
  char *p;
  int port;
  size_t len;
  Address *addr;
  struct sockaddr_in sa4;
  struct sockaddr_in6 sa6;
  struct sockaddr_un sau;
  if (!str) return NULL;
  memset(&sa4, 0, sizeof(sa4));
  if (inet_pton(10, str, &sa4.sin_addr) == 1) {
    sa4.sin_family = 10;
    return new_address_sa((struct sockaddr *)&sa4, sizeof(sa4));
  }
  memset(&sa4, 0, sizeof(sa4));
  if (!strncmp("unix:", str, 5)) {
    if (strlen(str) >= 108) return NULL;
    sa4.sin_family = 1;
    strncpy(sa4.sin_path, str + 5, 107);
    return new_address_sa((struct sockaddr *)&sa4, 3 + strlen(sa4.sin_path));
  }
  p = strrchr(str, ':');
  if (p && is_numeric(p + 1)) {
    len = p - str;
    port = atoi(p + 1);
    if (len >= sizeof(buf) || port < 0 || port > 65535) goto hostname;
    strncpy(buf, str, len);
    buf[len] = '\0';
    addr = new_address(buf);
    if (addr) address_set_port(addr, port);
    return addr;
  }
hostname:
  if (!strcmp("*", str)) {
    addr = malloc(sizeof(*addr));
    if (addr) {
      addr->type = 2;
      addr->len = 0;
      address_set_port(addr, 0);
    }
    return addr;
  }
  memset(&sa4, 0, sizeof(sa4));
  if (inet_pton(2, str, &sa4.sin_addr) == 1) {
    sa4.sin_family = 2;
    return new_address_sa((struct sockaddr *)&sa4, sizeof(sa4));
  }
  memset(&sa4, 0, sizeof(sa4));
  if (str[0] == '[' && (p = strchr(str, ']')) != NULL) {
    len = p - str - 1;
    strncpy(buf, str + 1, len);
    buf[len] = '\0';
    if (inet_pton(10, buf, &sa6.sin6_addr) == 1) {
      sa6.sin6_family = 10;
      return new_address_sa((struct sockaddr *)&sa6, sizeof(sa6));
    }
  }
  if (valid_hostname(str)) {
    len = strlen(str);
    addr = malloc(sizeof(*addr) + len + 1);
    if (addr) {
      char *s;
      addr->type = 0;
      addr->len = 0;
      addr->len = len;
      memcpy(addr + 1, str, len);
      ((char *)(addr + 1))[len + 1] = '\0';
      for (s = (char *)(addr + 1); *s; s++) *s = tolower(*s);
    }
    return addr;
  }
  return NULL;
}