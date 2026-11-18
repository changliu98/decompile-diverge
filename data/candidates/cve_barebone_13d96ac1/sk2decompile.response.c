static int print_media_desc(const pjmedia_sdp_media *m, char *buf,
                            pj_size_t buf_size) {
  char *p = buf;
  char *end = buf + buf_size;
  unsigned i;
  int ret;
  if (buf_size < m->fmtp.size + m->fmt.size + 36) return -1;
  *p++ = 'm';
  *p++ = '=';
  pj_memcpy(p, m->fmt.ptr, m->fmt.size);
  p += m->fmt.size;
  *p++ = ' ';
  p += pj_utoa(m->fmtp.clock_rate, p);
  if (m->fmtp.channels > 1) {
    *p++ = '/';
    p += pj_utoa(m->fmtp.channels, p);
  }
  *p++ = ' ';
  pj_memcpy(p, m->fmtp.ptr, m->fmtp.size);
  p += m->fmtp.size;
  for (i = 0; i < m->num_fmtp_attr; i++) {
    *p++ = ' ';
    pj_memcpy(p, m->fmtp_attr[i].ptr, m->fmtp_attr[i].size);
    p += m->fmtp_attr[i].size;
  }
  *p++ = '\r';
  *p++ = '\n';
  if (m->conn) {
    ret = print_connection_info(m->conn, p, end - p);
    if (ret < 0) return -1;
    p += ret;
  }
  for (i = 0; i < m->num_bw; i++) {
    ret = print_bandw(m->bw[i], p, end - p);
    if (ret < 0) return -1;
    p += ret;
  }
  for (i = 0; i < m->num_attr; i++) {
    ret = print_attr(m->attr[i], p, end - p);
    if (ret < 0) return -1;
    p += ret;
  }
  return p - buf;
}