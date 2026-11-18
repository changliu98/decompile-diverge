void ssdp_recv(int sd)
{
 char buf[512];
 socklen_t salen;
 struct sockaddr_in sa;
 struct ifsock *ifs;
 char *type;
 char *st;
 char *end;
 char *ptr;
 int i;

 memset(buf, 0, sizeof(buf));

 len = recvfrom(sd, buf, sizeof(buf), 0x40, (struct sockaddr *)&sa, &salen);
 if (len <= 0)
  return;

 buf[len] = '\0';

 if (sa.sin_family != 2)
  return;

 if (strstr(buf, "M-SEARCH *") == NULL)
  return;

 ifs = find_outbound(&sa);
 if (ifs == NULL) {
  syslog(LOG_INFO, "No matching socket for client %s", inet_ntoa(sa.sin_addr));
  return;
 }

 syslog(LOG_INFO, "Matching socket for client %s", inet_ntoa(sa.sin_addr));

 st = strcasestr(buf, "\r\nST:");
 if (st == NULL) {
  syslog(LOG_INFO, "No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
  send_message(ifs, "ssdp:all", &sa);
  return;
 }

 type = strchr(st, ':');
 if (type == NULL)
  return;

 type++;
 while ((*__ctype_b_loc ())[(int) ((* (unsigned char *) type))] & 0x2000)
  type++;

 end = strstr(type, "\r\n");
 if (end == NULL)
  return;

 *end = '\0';

 for (i = 0; supported_types[i] != NULL; i++) {
  if (!strcmp(supported_types[i], type))
   break;
 }

 if (supported_types[i] == NULL) {
  syslog(LOG_INFO, "M-SEARCH * for unsupported ST: %s from %s", type, inet_ntoa(sa.sin_addr));
  return;
 }

 syslog(LOG_INFO, "M-SEARCH * ST: %s from %s port %d", type, inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));

 send_message(ifs, type, &sa);
}