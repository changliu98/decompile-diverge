void __cdecl ssdp_recv(int sd)
{
  char *v1; // rax
  char *v2; // rax
  uint16_t v3; // ax
  char *v4; // rax
  char *v5; // [rsp+18h] [rbp-268h]
  ifsock *ifs; // [rsp+28h] [rbp-258h]
  const char *type; // [rsp+30h] [rbp-250h]
  char *typea; // [rsp+30h] [rbp-250h]
  char *typeb; // [rsp+30h] [rbp-250h]
  char *ptr; // [rsp+38h] [rbp-248h]
  size_t i; // [rsp+40h] [rbp-240h]
  char buf[512]; // [rsp+50h] [rbp-230h] BYREF
  socklen_t salen; // [rsp+25Ch] [rbp-24h] BYREF
  sockaddr sa; // [rsp+260h] [rbp-20h] BYREF
  ssize_t len; // [rsp+270h] [rbp-10h]
  int sda; // [rsp+27Ch] [rbp-4h]

  sda = sd;
  memset(buf, 0, sizeof(buf));
  len = recvfrom(sda, buf, 0x200uLL, 64, &sa, &salen);
  if ( len > 0 )
  {
    buf[len] = 0;
    if ( sa.sa_family == 2 )
    {
      if ( strstr(buf, "M-SEARCH *") )
      {
        ifs = find_outbound(&sa);
        if ( ifs )
        {
          v2 = inet_ntoa(*(struct in_addr *)&sa.sa_data[2]);
          syslog(7, "Matching socket for client %s", v2);
          type = strcasestr(buf, "\r\nST:");
          if ( type )
          {
            typea = strchr(type, 58);
            if ( typea )
            {
              for ( typeb = typea + 1; ((*__ctype_b_loc())[*typeb] & 0x2000) != 0; ++typeb )
                ;
              ptr = strstr(typeb, "\r\n");
              if ( ptr )
              {
                *ptr = 0;
                for ( i = 0LL; *(&supported_types + i); ++i )
                {
                  if ( !strcmp((const char *)*(&supported_types + i), typeb) )
                  {
                    v5 = inet_ntoa(*(struct in_addr *)&sa.sa_data[2]);
                    v3 = ntohs(*(uint16_t *)sa.sa_data);
                    syslog(7, "M-SEARCH * ST: %s from %s port %d", typeb, v5, v3);
                    send_message(ifs, typeb, &sa);
                    return;
                  }
                }
                v4 = inet_ntoa(*(struct in_addr *)&sa.sa_data[2]);
                syslog(7, "M-SEARCH * for unsupported ST: %s from %s", typeb, v4);
              }
            }
          }
          else
          {
            syslog(7, "No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
            send_message(ifs, (char *)"ssdp:all", &sa);
          }
        }
        else
        {
          v1 = inet_ntoa(*(struct in_addr *)&sa.sa_data[2]);
          syslog(7, "No matching socket for client %s", v1);
        }
      }
    }
  }
}