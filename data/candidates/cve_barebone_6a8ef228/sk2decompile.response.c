void ssdp_recv(int sock) {
  struct sockaddr_in client;
  socklen_t len;
  char buf[512];
  char *st;
  char *st_start;
  char *st_end;
  char *st_search;
  int i;
  int client_len;
  struct outbound *outbound;
  memset(buf, 0, 512);
  len = recvfrom(sock, buf, 512, 64, (struct sockaddr *)&client, &client_len);
  if (len <= 0) return;
  buf[len] = 0;
  if (client.sin_family != 2) return;
  if (strstr(buf, "M-SEARCH *") == NULL) return;
  outbound = find_outbound(&client);
  if (outbound == NULL) {
    syslog(7, "No matching socket for client %s", inet_ntoa(client.sin_addr));
    return;
  }
  syslog(7, "Matching socket for client %s", inet_ntoa(client.sin_addr));
  st = strcasestr(buf, "\r\nST:");
  if (st == NULL) {
    syslog(
        7, "No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
    send_message(outbound, "ssdp:all", &client);
    return;
  }
  st_start = strchr(st, ':');
  if (st_start == NULL) return;
  st_start++;
  while (isspace(*st_start)) st_start++;
  st_end = strstr(st_start, "\r\n");
  if (st_end == NULL) return;
  *st_end = 0;
  for (i = 0; st_list[i] != NULL; i++) {
    if (!strcmp(st_list[i], st_start)) {
      syslog(7, "M-SEARCH * ST: %s from %s port %d", st_start,
             inet_ntoa(client.sin_addr), ntohs(client.sin_port));
      send_message(outbound, st_start, &client);
      return;
    }
  }
  syslog(7, "M-SEARCH * for unsupported ST: %s from %s", st_start,
         inet_ntoa(client.sin_addr));
}