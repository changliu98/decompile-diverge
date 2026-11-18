void __cdecl ssdp_recv(int sd)
{
  char buf[512];
  struct sockaddr_in sa;
  socklen_t salen;
  ssize_t len;

  memset(buf, 0, sizeof(buf));
  
  // MSG_WAITALL is typically 0x40 on Linux
  len = recvfrom(sd, buf, sizeof(buf) - 1, 0x40, (struct sockaddr *)&sa, &salen);
  
  if (len > 0)
  {
    buf[len] = '\0';
    
    // AF_INET is 2
    if (sa.sin_family == AF_INET)
    {
      if (strstr(buf, "M-SEARCH *"))
      {
        ifsock *ifs = find_outbound((struct sockaddr *)&sa);
        if (ifs)
        {
          syslog(LOG_DEBUG, "Matching socket for client %s", inet_ntoa(sa.sin_addr));
          
          char *st_header = strcasestr(buf, "\r\nST:");
          if (st_header)
          {
            char *st_value = strchr(st_header, ':');
            if (st_value)
            {
              // Skip whitespace after the colon
              while ((*__ctype_b_loc())[*st_value] & _ISspace)
                st_value++;
                
              char *header_end = strstr(st_value, "\r\n");
              if (header_end)
              {
                *header_end = '\0';
                
                for (size_t i = 0; supported_types[i]; ++i)
                {
                  if (!strcmp(supported_types[i], st_value))
                  {
                    syslog(LOG_DEBUG, "M-SEARCH * ST: %s from %s port %d", 
                           st_value, inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
                           
                    send_message(ifs, st_value, (struct sockaddr *)&sa);
                    return;
                  }
                }
                syslog(LOG_DEBUG, "M-SEARCH * for unsupported ST: %s from %s", 
                       st_value, inet_ntoa(sa.sin_addr));
              }
            }
          }
          else
          {
            syslog(LOG_DEBUG, "No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
            send_message(ifs, "ssdp:all", (struct sockaddr *)&sa);
          }
        }
        else
        {
          syslog(LOG_DEBUG, "No matching socket for client %s", inet_ntoa(sa.sin_addr));
        }
      }
    }
  }
}