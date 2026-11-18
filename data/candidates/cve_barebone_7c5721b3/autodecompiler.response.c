struct address *address_parse(char *address) {
 if (!address) return NULL;

 struct sockaddr_storage addr;
 memset(&addr, 0, sizeof(struct sockaddr_storage));

 if (inet_pton(10, address, &((struct sockaddr_in6 *)&addr)->sin6_addr) == 1) {
  ((struct sockaddr_in6 *)&addr)->sin6_family = 10;
  return new_address_sa((struct sockaddr *)&addr, sizeof(struct sockaddr_in6));
 }

 memset(&addr, 0, sizeof(struct sockaddr_storage));
 if (strncmp("unix:", address, 5) == 0) {
  if (strlen(address) >= 128 - sizeof(struct sockaddr_un) + 1) return NULL;
  ((struct sockaddr_un *)&addr)->sun_family = 1;
  strncpy(((struct sockaddr_un *)&addr)->sun_path, address + 5, 128 - 1);
  return new_address_sa((struct sockaddr *)&addr, sizeof(struct sockaddr_un) - 1 + strlen(((struct sockaddr_un *)&addr)->sun_path));
 }

 char *port = strrchr(address, ':');
 if (port && is_numeric(port + 1)) {
  size_t len = port - address;
  int p = atoi(port + 1);
  if (len < 263 && p >= 0 && p <= 0xffff) {
   char ip[263];
   strncpy(ip, address, len);
   ip[len] = '\0';
   struct address *a = new_address(ip);
   if (a) address_set_port(a, (unsigned short)p);
   return a;
  }
 }

 if (strcmp("*", address) == 0) {
  struct address *a = malloc(sizeof(struct address) + 2);
  if (a) {
   a->type = 2;
   a->port = 0;
   address_set_port(a, 0);
  }
  return a;
 }

 memset(&addr, 0, sizeof(struct sockaddr_storage));
 if (inet_pton(2, address, &((struct sockaddr_in *)&addr)->sin_addr) == 1) {
  ((struct sockaddr_in *)&addr)->sin_family = 2;
  return new_address_sa((struct sockaddr *)&addr, sizeof(struct sockaddr_in));
 }

 memset(&addr, 0, sizeof(struct sockaddr_storage));
 if (*address == '[') {
  port = strchr(address, ']');
  if (port) {
   size_t len = port - address - 1;
   char ip[263];
   strncpy(ip, address + 1, len);
   ip[len] = '\0';
   if (inet_pton(10, ip, &((struct sockaddr_in6 *)&addr)->sin6_addr) == 1) {
    ((struct sockaddr_in6 *)&addr)->sin6_family = 10;
    return new_address_sa((struct sockaddr *)&addr, sizeof(struct sockaddr_in6));
   }
  }
 }

 if (valid_hostname(address)) {
  size_t len = strlen(address);
  struct address *a = malloc(sizeof(struct address) + 18 + len + 1);
  if (a) {
   a->type = 0;
   a->port = 0;
   a->hlen = (unsigned short)len;
   memcpy((char *)a + 18, address, len);
   ((char *)a)[18 + a->hlen] = '\0';
   char *c = (char *)a + 18;
   while (*c) {
    *c = tolower(*c);
    c++;
   }
  }
  return a;
 }

 return NULL;
}