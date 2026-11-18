Address *__cdecl new_address(const char *hostname_or_ip)
{
  int v1; // eax
  char *c; // [rsp+8h] [rbp-1D8h]
  Address *addr_1; // [rsp+10h] [rbp-1D0h]
  Address *addr_0; // [rsp+18h] [rbp-1C8h]
  Address *addr; // [rsp+20h] [rbp-1C0h]
  unsigned int port_num; // [rsp+2Ch] [rbp-1B4h]
  unsigned __int64 len; // [rsp+30h] [rbp-1B0h]
  signed __int64 lenb; // [rsp+30h] [rbp-1B0h]
  size_t lena; // [rsp+30h] [rbp-1B0h]
  char *port; // [rsp+38h] [rbp-1A8h]
  char ip_buf[262]; // [rsp+40h] [rbp-1A0h] BYREF
  union {sockaddr a;sockaddr_in in;sockaddr_in6 in6;sockaddr_un un;sockaddr_storage s;} s; // [rsp+150h] [rbp-90h] BYREF
  const char *hostname_or_ipa; // [rsp+1D0h] [rbp-10h]

  hostname_or_ipa = hostname_or_ip;
  if ( !hostname_or_ip )
    return 0LL;
  memset(&s, 0, sizeof(s));
  if ( inet_pton(10, hostname_or_ipa, &s.s.__ss_padding[6]) == 1 )
  {
    s.a.sa_family = 10;
    return new_address_sa(&s.a, 0x1Cu);
  }
  else
  {
    memset(&s, 0, sizeof(s));
    if ( !strncmp("unix:", hostname_or_ipa, 5uLL) )
    {
      if ( strlen(hostname_or_ipa) < 0x6C )
      {
        s.a.sa_family = 1;
        strncpy(s.a.sa_data, hostname_or_ipa + 5, 0x6BuLL);
        v1 = strlen(s.a.sa_data);
        return new_address_sa(&s.a, v1 + 3);
      }
      else
      {
        return 0LL;
      }
    }
    else
    {
      port = strrchr(hostname_or_ipa, 58);
      if ( port
        && is_numeric(port + 1)
        && (len = port - hostname_or_ipa, port_num = atoi(port + 1), len < 0x106)
        && port_num <= 0xFFFF )
      {
        strncpy(ip_buf, hostname_or_ipa, len);
        ip_buf[len] = 0;
        addr = new_address(ip_buf);
        if ( addr )
          address_set_port(addr, port_num);
        return addr;
      }
      else if ( !strcmp("*", hostname_or_ipa) )
      {
        addr_0 = (Address *)malloc(0x18uLL);
        if ( addr_0 )
        {
          addr_0->type = 2;
          addr_0->len = 0LL;
          address_set_port(addr_0, 0);
        }
        return addr_0;
      }
      else
      {
        memset(&s, 0, sizeof(s));
        if ( inet_pton(2, hostname_or_ipa, &s.un.sun_path[2]) == 1 )
        {
          s.a.sa_family = 2;
          return new_address_sa(&s.a, 0x10u);
        }
        else
        {
          memset(&s, 0, sizeof(s));
          if ( *hostname_or_ipa == 91
            && (port = strchr(hostname_or_ipa, 93)) != 0LL
            && (lenb = port - hostname_or_ipa - 1,
                strncpy(ip_buf, hostname_or_ipa + 1, lenb),
                ip_buf[lenb] = 0,
                inet_pton(10, ip_buf, &s.s.__ss_padding[6]) == 1) )
          {
            s.a.sa_family = 10;
            return new_address_sa(&s.a, 0x1Cu);
          }
          else if ( valid_hostname(hostname_or_ipa) )
          {
            lena = strlen(hostname_or_ipa);
            addr_1 = (Address *)malloc(lena + 19);
            if ( addr_1 )
            {
              addr_1->type = 0;
              addr_1->port = 0;
              addr_1->len = lena;
              memcpy(&addr_1->port + 1, hostname_or_ipa, lena);
              *((_BYTE *)&addr_1->port + addr_1->len + 2) = 0;
              for ( c = (char *)(&addr_1->port + 1); *c; ++c )
                *c = tolower(*c);
            }
            return addr_1;
          }
          else
          {
            return 0LL;
          }
        }
      }
    }
  }
}