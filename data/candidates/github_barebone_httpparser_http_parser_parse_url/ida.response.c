int __cdecl http_parser_parse_url(const char *buf, size_t buflen, int is_connect, http_parser_url *u)
{
  int v4; // eax
  unsigned __int64 v; // [rsp+10h] [rbp-60h]
  const char *p_0; // [rsp+20h] [rbp-50h]
  uint16_t len; // [rsp+28h] [rbp-48h]
  uint16_t off; // [rsp+2Ah] [rbp-46h]
  int found_at; // [rsp+2Ch] [rbp-44h]
  http_parser_url_fields old_uf; // [rsp+30h] [rbp-40h]
  http_parser_url_fields uf; // [rsp+34h] [rbp-3Ch]
  const char *p; // [rsp+38h] [rbp-38h]
  state s; // [rsp+44h] [rbp-2Ch]

  found_at = 0;
  if ( !buflen )
    return 1;
  u->field_set = 0;
  u->port = 0;
  v4 = 20;
  if ( is_connect )
    v4 = 24;
  s = v4;
  old_uf = http_parser_url_fields::UF_MAX;
  for ( p = buf; p < &buf[buflen]; ++p )
  {
    s = parse_url_char(s, *p);
    switch ( s )
    {
      case state::s_dead:
        return 1;
      case state::s_req_schema:
        uf = http_parser_url_fields::UF_SCHEMA;
        break;
      case state::s_req_schema_slash:
      case state::s_req_schema_slash_slash:
      case state::s_req_server_start:
      case state::s_req_query_string_start:
      case state::s_req_fragment_start:
        continue;
      case state::s_req_server:
        goto LABEL_11;
      case state::s_req_server_with_at:
        found_at = 1;
LABEL_11:
        uf = http_parser_url_fields::UF_HOST;
        break;
      case state::s_req_path:
        uf = http_parser_url_fields::UF_PATH;
        break;
      case state::s_req_query_string:
        uf = http_parser_url_fields::UF_QUERY;
        break;
      case state::s_req_fragment:
        uf = http_parser_url_fields::UF_FRAGMENT;
        break;
      default:
        __assert_fail(
          "!\"Unexpected state\"",
          "./func.c",
          0x9B0u,
          "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)");
    }
    if ( uf == old_uf )
    {
      ++u->field_data[uf].len;
    }
    else
    {
      u->field_data[uf].off = (_WORD)p - (_WORD)buf;
      u->field_data[uf].len = 1;
      u->field_set |= 1 << uf;
      old_uf = uf;
    }
  }
  if ( (u->field_set & 1) != 0 && (u->field_set & 2) == 0 )
    return 1;
  if ( (u->field_set & 2) != 0 && http_parse_host(buf, u, found_at) )
    return 1;
  if ( is_connect && u->field_set != 6 )
    return 1;
  if ( (u->field_set & 4) != 0 )
  {
    off = u->field_data[2].off;
    len = u->field_data[2].len;
    if ( len + off > buflen )
      __assert_fail(
        "(size_t) (off + len) <= buflen && \"Port number overflow\"",
        "./func.c",
        0x9DFu,
        "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)");
    v = 0LL;
    for ( p_0 = &buf[off]; p_0 < &buf[off + len]; ++p_0 )
    {
      v = 10 * v + *p_0 - 48;
      if ( v > 0xFFFF )
        return 1;
    }
    u->port = v;
  }
  return 0;
}