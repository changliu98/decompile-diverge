void process_msearch(int sock)
{
 char buf[512];
 struct sockaddr_in cl_addr;
 int len, i;
 struct ssdpd_s *ssdpd;
 struct ssdpd_s *ssdpd_ptr;
 struct sockaddr_in *cl_addr_ptr;
 char *st, *end_st, *c;
 unsigned int cl_addr_size;

 memset(buf, 0, sizeof(buf));
 cl_addr_size = sizeof(cl_addr);
 len = recvfrom(sock, buf, sizeof(buf), 0,
  (struct sockaddr *)&cl_addr, &cl_addr_size);

 if (len > 0) {
  buf[len] = '\0';
  if (cl_addr.sin_family != AF_INET)
   return;

  if (strstr(buf, "M-SEARCH *")) {

   cl_addr_ptr = &cl_addr;


   ssdpd = find_outbound(&cl_addr);
   if (!ssdpd) {
    syslog(7, "No matching socket for client %s",
     inet_ntoa(cl_addr_ptr->sin_addr));
    return;
   }
   syslog(7, "Matching socket for client %s",
    inet_ntoa(cl_addr_ptr->sin_addr));

   st = strcasestr(buf, "\r\nST:");
   if (!st) {
    syslog(7, "No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
    st = "ssdp:all";
    send_message(ssdpd, st, &cl_addr);
   } else {
    st = strchr(st, ':');
    if (!st)
     return;

    st++;
    while ((*(___ctype_b_loc ())[(int)((*st))] & (unsigned short int) 8192))
     st++;

    end_st = strstr(st, "\r\n");
    if (!end_st)
     return;

    *end_st = '\0';

    for (i = 0; supported_types[i]; i++) {
     if (!strcmp(supported_types[i], st)) {
      syslog(7, "M-SEARCH * ST: %s from %s port %d",
       st, inet_ntoa(cl_addr_ptr->sin_addr),
       ntohs(cl_addr_ptr->sin_port));
      send_message(ssdpd, st, &cl_addr);
      return;
     }
    }

    syslog(7, "M-SEARCH * for unsupported ST: %s from %s",
     st, inet_ntoa(cl_addr_ptr->sin_addr));
   }
  }
 }
}