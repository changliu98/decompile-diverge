int __cdecl print_media_desc(const pjmedia_sdp_media *m, char *buf, pj_size_t len)
{
  int printed;
  unsigned int i;
  char *end;
  char *p;

  end = &buf[len];
  
  // Check if the buffer has enough space for the basic media description
  if (len < m->desc.transport.slen + m->desc.media.slen + 36)
    return -1;

  // Write "m="
  buf[0] = 'm';
  buf[1] = '=';
  
  // Write media type (e.g., "audio", "video")
  pj_memcpy(buf + 2, m->desc.media.ptr, m->desc.media.slen);
  p = &buf[m->desc.media.slen + 2];
  
  // Write port number
  *p = ' ';
  p += pj_utoa(m->desc.port, p + 1) + 1;
  
  // Write port count if greater than 1
  if (m->desc.port_count > 1)
  {
    *p = '/';
    p += pj_utoa(m->desc.port_count, p + 1) + 1;
  }
  
  // Write transport protocol (e.g., "RTP/AVP")
  *p = ' ';
  p++;
  pj_memcpy(p, m->desc.transport.ptr, m->desc.transport.slen);
  p += m->desc.transport.slen;
  
  // Write format list
  for (i = 0; i < m->desc.fmt_count; ++i)
  {
    *p = ' ';
    p++;
    pj_memcpy(p, m->desc.fmt[i].ptr, m->desc.fmt[i].slen);
    p += m->desc.fmt[i].slen;
  }
  
  // Terminate the line with CRLF
  *p = '\r';
  p++;
  *p = '\n';
  p++;

  // Write connection info if present
  if (m->conn)
  {
    printed = print_connection_info(m->conn, p, (int)(end - p));
    if (printed < 0)
      return -1;
    p += printed;
  }

  // Write bandwidth info
  for (i = 0; i < m->bandw_count; ++i)
  {
    printed = print_bandw(m->bandw[i], p, end - p);
    if (printed < 0)
      return -1;
    p += printed;
  }

  // Write attributes
  for (i = 0; i < m->attr_count; ++i)
  {
    printed = print_attr(m->attr[i], p, end - p);
    if (printed < 0)
      return -1;
    p += printed;
  }

  return (int)(p - buf);
}