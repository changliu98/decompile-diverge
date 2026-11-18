void ssdp_recv(int sd)

{
  uint16_t uVar1;
  int iVar2;
  ssize_t sVar3;
  char *pcVar4;
  ifsock *ifs_00;
  ushort **ppuVar5;
  sockaddr_in *sin;
  ifsock *ifs;
  char *type;
  char *ptr;
  size_t i;
  char buf [512];
  socklen_t salen;
  sockaddr sa;
  ssize_t len;
  int sd_local;
  
  memset(buf,0,0x200);
  sVar3 = recvfrom(sd,buf,0x200,0x40,(sockaddr *)&sa,&salen);
  if (((0 < sVar3) && (buf[sVar3] = '\0', sa.sa_family == 2)) &&
     (pcVar4 = strstr(buf,"M-SEARCH *"), pcVar4 != (char *)0x0)) {
    ifs_00 = find_outbound(&sa);
    if (ifs_00 == (ifsock *)0x0) {
      pcVar4 = inet_ntoa((in_addr)sa.sa_data._2_4_);
      syslog(7,"No matching socket for client %s",pcVar4);
    }
    else {
      pcVar4 = inet_ntoa((in_addr)sa.sa_data._2_4_);
      syslog(7,"Matching socket for client %s",pcVar4);
      pcVar4 = strcasestr(buf,"\r\nST:");
      if (pcVar4 == (char *)0x0) {
        syslog(7,"No Search Type (ST:) found in M-SEARCH *, assuming ssdp:all");
        send_message(ifs_00,"ssdp:all",&sa);
      }
      else {
        type = strchr(pcVar4,0x3a);
        if (type != (char *)0x0) {
          do {
            type = type + 1;
            ppuVar5 = __ctype_b_loc();
          } while (((*ppuVar5)[(int)*type] & 0x2000) != 0);
          pcVar4 = strstr(type,"\r\n");
          if (pcVar4 != (char *)0x0) {
            *pcVar4 = '\0';
            for (i = 0; supported_types[i] != (char *)0x0; i = i + 1) {
              iVar2 = strcmp(supported_types[i],type);
              if (iVar2 == 0) {
                pcVar4 = inet_ntoa((in_addr)sa.sa_data._2_4_);
                uVar1 = ntohs(sa.sa_data._0_2_);
                syslog(7,"M-SEARCH * ST: %s from %s port %d",type,pcVar4,(ulong)uVar1);
                send_message(ifs_00,type,&sa);
                return;
              }
            }
            pcVar4 = inet_ntoa((in_addr)sa.sa_data._2_4_);
            syslog(7,"M-SEARCH * for unsupported ST: %s from %s",type,pcVar4);
          }
        }
      }
    }
  }
  return;
}