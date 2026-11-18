pj_status_t __cdecl pjstun_parse_msg(void *buf, pj_size_t buf_len, pjstun_msg *msg)
{
  pj_uint16_t v3; // ax
  int v5; // [rsp+Ch] [rbp-44h]
  unsigned int len; // [rsp+14h] [rbp-3Ch]
  pjstun_attr_hdr **attr; // [rsp+18h] [rbp-38h]
  char *p_attr; // [rsp+20h] [rbp-30h]
  pj_uint16_t msg_len; // [rsp+2Ch] [rbp-24h]

  msg->hdr = (pjstun_msg_hdr *)buf;
  v5 = foldCase(msg->hdr->type);
  if ( (unsigned int)(v5 - 1) >= 2 && (unsigned int)(v5 - 257) >= 2 && (unsigned int)(v5 - 273) > 1 )
    return 320002;
  v3 = foldCase(msg->hdr->length);
  msg_len = v3;
  if ( v3 != buf_len - 20 )
    return 320003;
  msg->attr_count = 0;
  p_attr = (char *)buf + 20;
  while ( msg_len )
  {
    attr = &msg->attr[msg->attr_count];
    *attr = (pjstun_attr_hdr *)p_attr;
    len = (foldCase((*attr)->length) + 7) & 0xFFFFFFFC;
    if ( msg_len < len )
      return 320004;
    foldCase((*attr)->type);
    msg_len -= len;
    p_attr += len;
    ++msg->attr_count;
  }
  return 0;
}