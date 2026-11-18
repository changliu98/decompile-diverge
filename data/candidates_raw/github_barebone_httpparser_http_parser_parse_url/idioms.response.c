int http_parser_parse_url(const char *buf, unsigned long buflen, int is_connect, struct http_parser_url *u) {
  enum state s = s_start;
  enum http_parser_url_fields uf = UF_MAX;
  enum http_parser_url_fields old_uf = UF_MAX;
  int found_at = 0;
  if (buflen == 0)
    return 1;
  u->field_set = 0;
  u->port = 0;
  s = s_req_schema;
  if (is_connect)
    s = s_req_connect;
  for (const char *p = (const char *) buf; p < (const char *) (buf + buflen); p++) {
    s = parse_url_char(s, *p);
    switch (s) {
      case s_start:
      case s_req_schema:
      case s_req_schema_slash:
      case s_req_schema_slash_slash:
      case s_req_server_start:
      case s_req_query_string_start:
      case s_req_fragment_start:
        break;
      case s_req_server:
      case s_req_server_with_at:
        found_at = 1;
      case s_req_path:
      case s_req_query_string:
      case s_req_fragment:
        break;
      case s_dead:
        return 1;
      default:
        break;
    }
    switch (s) {
      case s_req_schema:
        uf = UF_SCHEMA;
        break;
      case s_req_server:
      case s_req_server_with_at:
        uf = UF_HOST;
        break;
      case s_req_path:
        uf = UF_PATH;
        break;
      case s_req_query_string:
        uf = UF_QUERY;
        break;
      case s_req_fragment:
        uf = UF_FRAGMENT;
        break;
      default:
        break;
    }
    if (uf == old_uf) {
      u->field_data[uf].len++;
    } else {
      u->field_data[uf].off = p - buf;
      u->field_data[uf].len = 1;
      u->field_set |= (1 << uf);
      old_uf = uf;
    }
  }
  if ((u->field_set & (1 << UF_SCHEMA)) && !(u->field_set & (1 << UF_HOST)))
    return 1;
  if ((u->field_set & (1 << UF_HOST)) &&
      http_parse_host(buf, u, found_at))
    return 1;
  if (is_connect && (u->field_set & (1 << UF_HOST)) != (1 << UF_HOST))
    return 1;
  if ((u->field_set & (1 << UF_PORT))) {
    unsigned short off = u->field_data[UF_PORT].off;
    unsigned short len = u->field_data[UF_PORT].len;
    ((void) sizeof (((size_t) (off + len) <= buflen && "Port number overflow") ? 1 : 0), __extension__ ({ if ((size_t) (off + len) <= buflen && "Port number overflow") ; else __assert_fail ("(size_t) (off + len) <= buflen && \"Port number overflow\"", "./func.c", 251, __extension__ __PRETTY_FUNCTION__); }));
    unsigned long port = 0;
    for (const char *p = (const char *) (buf + off); p < (const char *) (buf + off + len); p++) {
      port = port * 10 + *p - '0';
      if (port > 65535)
        return 1;
    }
    u->port = (unsigned short) port;
  }
  return 0;
}