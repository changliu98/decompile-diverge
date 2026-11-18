int SSL_select_next_proto(unsigned char **pnext, unsigned char *plen,
                          const unsigned char *client, unsigned int client_len,
                          const unsigned char *server,
                          unsigned int server_len) {
  unsigned int i, j;
  int ret;
  for (i = 0; i < client_len; i += client[i] + 1) {
    for (j = 0; j < server_len; j += server[j] + 1) {
      if (client[i] == server[j] &&
          !memcmp(client + i + 1, server + j + 1, client[i])) {
        *pnext = (unsigned char *)(client + i + 1);
        *plen = client[i];
        ret = 1;
        goto found;
      }
    }
  }
  *pnext = (unsigned char *)server;
  *plen = server[0];
  ret = 2;
found:
  return ret;
}