int print_media_desc(pjmedia_sdp_media *m,char *buf,pj_size_t len)

{
  int iVar1;
  char *pcVar2;
  pj_ssize_t pVar3;
  char *pcVar4;
  int printed;
  uint i;
  char *end;
  char *p;
  pj_size_t len_local;
  char *buf_local;
  pjmedia_sdp_media *m_local;
  int local_c;
  
  pcVar2 = buf + len;
  if (len < (m->desc).media.slen + (m->desc).transport.slen + 0x24U) {
    local_c = -1;
  }
  else {
    *buf = 'm';
    pcVar4 = buf + 2;
    buf[1] = '=';
    pj_memcpy(pcVar4,(m->desc).media.ptr,(m->desc).media.slen);
    pcVar4 = pcVar4 + (m->desc).media.slen;
    *pcVar4 = ' ';
    iVar1 = pj_utoa((ulong)(m->desc).port,pcVar4 + 1);
    p = pcVar4 + 1 + iVar1;
    if (1 < (m->desc).port_count) {
      *p = '/';
      iVar1 = pj_utoa((ulong)(m->desc).port_count,p + 1);
      p = p + 1 + iVar1;
    }
    *p = ' ';
    pj_memcpy(p + 1,(m->desc).transport.ptr,(m->desc).transport.slen);
    p = p + 1 + (m->desc).transport.slen;
    for (i = 0; i < (m->desc).fmt_count; i = i + 1) {
      *p = ' ';
      pj_memcpy(p + 1,(m->desc).fmt[i].ptr,(m->desc).fmt[i].slen);
      p = p + 1 + (m->desc).fmt[i].slen;
    }
    pcVar4 = p + 1;
    *p = '\r';
    p = p + 2;
    *pcVar4 = '\n';
    if (m->conn != (pjmedia_sdp_conn *)0x0) {
      iVar1 = print_connection_info(m->conn,p,(int)pcVar2 - (int)p);
      if (iVar1 < 0) {
        return -1;
      }
      p = p + iVar1;
    }
    for (i = 0; i < m->bandw_count; i = i + 1) {
      pVar3 = print_bandw(m->bandw[i],p,(long)pcVar2 - (long)p);
      if ((int)pVar3 < 0) {
        return -1;
      }
      p = p + (int)pVar3;
    }
    for (i = 0; i < m->attr_count; i = i + 1) {
      pVar3 = print_attr(m->attr[i],p,(long)pcVar2 - (long)p);
      if ((int)pVar3 < 0) {
        return -1;
      }
      p = p + (int)pVar3;
    }
    local_c = (int)p - (int)buf;
  }
  return local_c;
}