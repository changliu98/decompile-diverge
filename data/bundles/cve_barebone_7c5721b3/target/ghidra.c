Address * new_address(char *hostname_or_ip)

{
  long lVar1;
  int iVar2;
  size_t sVar3;
  char *pcVar4;
  ulong __n;
  Address *pAVar5;
  char *c;
  Address *addr_2;
  Address *addr_1;
  Address *addr;
  int port_num;
  size_t len;
  char *port;
  char ip_buf [262];
  anon_union_128_5_78ec6f73 s;
  char *hostname_or_ip_local;
  Address *local_10;
  
  if (hostname_or_ip == (char *)0x0) {
    local_10 = (Address *)0x0;
  }
  else {
    hostname_or_ip_local = hostname_or_ip;
    memset(&s,0,0x80);
    iVar2 = inet_pton(10,hostname_or_ip_local,s.a.sa_data + 6);
    if (iVar2 == 1) {
      s.a.sa_family = 10;
      local_10 = new_address_sa(&s.a,0x1c);
    }
    else {
      memset(&s,0,0x80);
      iVar2 = strncmp("unix:",hostname_or_ip_local,5);
      if (iVar2 == 0) {
        sVar3 = strlen(hostname_or_ip_local);
        if (sVar3 < 0x6c) {
          s.a.sa_family = 1;
          strncpy(s.a.sa_data,hostname_or_ip_local + 5,0x6b);
          sVar3 = strlen(s.a.sa_data);
          local_10 = new_address_sa(&s.a,(int)sVar3 + 3);
        }
        else {
          local_10 = (Address *)0x0;
        }
      }
      else {
        pcVar4 = strrchr(hostname_or_ip_local,0x3a);
        if ((pcVar4 != (char *)0x0) && (iVar2 = is_numeric(pcVar4 + 1), iVar2 != 0)) {
          __n = (long)pcVar4 - (long)hostname_or_ip_local;
          iVar2 = atoi(pcVar4 + 1);
          if ((__n < 0x106) && ((-1 < iVar2 && (iVar2 < 0x10000)))) {
            strncpy(ip_buf,hostname_or_ip_local,__n);
            ip_buf[__n] = '\0';
            pAVar5 = new_address(ip_buf);
            if (pAVar5 == (Address *)0x0) {
              return (Address *)0x0;
            }
            address_set_port(pAVar5,(uint16_t)iVar2);
            return pAVar5;
          }
        }
        iVar2 = strcmp("*",hostname_or_ip_local);
        if (iVar2 == 0) {
          local_10 = malloc(0x18);
          if (local_10 != (Address *)0x0) {
            local_10->type = WILDCARD;
            local_10->len = 0;
            address_set_port(local_10,0);
          }
        }
        else {
          memset(&s,0,0x80);
          iVar2 = inet_pton(2,hostname_or_ip_local,s.a.sa_data + 2);
          if (iVar2 == 1) {
            s.a.sa_family = 2;
            local_10 = new_address_sa(&s.a,0x10);
          }
          else {
            memset(&s,0,0x80);
            if ((*hostname_or_ip_local == '[') &&
               (pcVar4 = strchr(hostname_or_ip_local,0x5d), pcVar4 != (char *)0x0)) {
              lVar1 = -1 - (long)hostname_or_ip_local;
              strncpy(ip_buf,hostname_or_ip_local + 1,(size_t)(pcVar4 + lVar1));
              ip_buf[(long)(pcVar4 + lVar1)] = '\0';
              iVar2 = inet_pton(10,ip_buf,s.a.sa_data + 6);
              if (iVar2 == 1) {
                s.a.sa_family = 10;
                pAVar5 = new_address_sa(&s.a,0x1c);
                return pAVar5;
              }
            }
            iVar2 = valid_hostname(hostname_or_ip_local);
            if (iVar2 == 0) {
              local_10 = (Address *)0x0;
            }
            else {
              sVar3 = strlen(hostname_or_ip_local);
              local_10 = malloc(sVar3 + 0x13);
              if (local_10 != (Address *)0x0) {
                local_10->type = HOSTNAME;
                local_10->port = 0;
                local_10->len = sVar3;
                memcpy(&local_10->field_0x12,hostname_or_ip_local,sVar3);
                (&local_10->field_0x12)[local_10->len] = 0;
                for (c = &local_10->field_0x12; *c != '\0'; c = c + 1) {
                  iVar2 = tolower((int)*c);
                  *c = (char)iVar2;
                }
              }
            }
          }
        }
      }
    }
  }
  return local_10;
}