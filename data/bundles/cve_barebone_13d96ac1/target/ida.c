int __cdecl print_media_desc(const pjmedia_sdp_media *m, char *buf, pj_size_t len)
{
  char *v3; // rax
  char *v4; // rax
  char *v5; // rax
  _BYTE *v6; // rax
  int printed; // [rsp+8h] [rbp-38h]
  int printeda; // [rsp+8h] [rbp-38h]
  int printedb; // [rsp+8h] [rbp-38h]
  unsigned int i; // [rsp+Ch] [rbp-34h]
  unsigned int ia; // [rsp+Ch] [rbp-34h]
  unsigned int ib; // [rsp+Ch] [rbp-34h]
  char *end; // [rsp+10h] [rbp-30h]
  char *p; // [rsp+18h] [rbp-28h]
  char *pc; // [rsp+18h] [rbp-28h]
  char *pa; // [rsp+18h] [rbp-28h]
  char *pd; // [rsp+18h] [rbp-28h]
  char *pb; // [rsp+18h] [rbp-28h]

  end = &buf[len];
  if ( len < m->desc.transport.slen + m->desc.media.slen + 36 )
    return -1;
  *buf = 109;
  buf[1] = 61;
  pj_memcpy(buf + 2, m->desc.media.ptr, m->desc.media.slen);
  v3 = &buf[m->desc.media.slen + 2];
  *v3 = 32;
  p = &v3[pj_utoa(m->desc.port, v3 + 1) + 1];
  if ( m->desc.port_count > 1 )
  {
    *p = 47;
    p += pj_utoa(m->desc.port_count, p + 1) + 1;
  }
  v4 = p;
  pc = p + 1;
  *v4 = 32;
  pj_memcpy(pc, m->desc.transport.ptr, m->desc.transport.slen);
  pa = &pc[m->desc.transport.slen];
  for ( i = 0; i < m->desc.fmt_count; ++i )
  {
    v5 = pa;
    pd = pa + 1;
    *v5 = 32;
    pj_memcpy(pd, m->desc.fmt[i].ptr, m->desc.fmt[i].slen);
    pa = &pd[m->desc.fmt[i].slen];
  }
  *pa = 13;
  v6 = pa + 1;
  pb = pa + 2;
  *v6 = 10;
  if ( m->conn )
  {
    printed = print_connection_info(m->conn, pb, (_DWORD)end - (_DWORD)pb);
    if ( printed < 0 )
      return -1;
    pb += printed;
  }
  for ( ia = 0; ia < m->bandw_count; ++ia )
  {
    printeda = print_bandw(m->bandw[ia], pb, end - pb);
    if ( printeda < 0 )
      return -1;
    pb += printeda;
  }
  for ( ib = 0; ib < m->attr_count; ++ib )
  {
    printedb = print_attr(m->attr[ib], pb, end - pb);
    if ( printedb < 0 )
      return -1;
    pb += printedb;
  }
  return (_DWORD)pb - (_DWORD)buf;
}