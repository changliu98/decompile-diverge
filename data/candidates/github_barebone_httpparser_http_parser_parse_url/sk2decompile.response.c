int http_parser_parse_url(const char *buf, unsigned buf_len, int is_connect,
                          struct http_parser_url *u) {
  const char *p;
  enum url_parse_state state;
  enum http_parser_url_fields field;
  enum http_parser_url_fields last_field;
  int is_ipv6 = 0;
  if (buf_len == 0) return 1;
  u->field_set = 0;
  u->port = 0;
  state = is_connect ? s_http_connect_url_schema : s_http_url_schema;
  last_field = UF_MAX;
  for (p = buf; p < buf + buf_len; p++) {
    state = parse_url_char(state, *p);
    switch (state) {
      case s_http_url_error:
        return 1;
      case s_http_url_schema_slash:
        field = UF_SCHEMA;
        break;
      case s_http_url_schema_slash_slash:
      case s_http_url_schema_slash_slash_host:
      case s_http_url_schema_slash_slash_host_port:
      case s_http_url_schema_slash_slash_host_port_path:
      case s_http_url_schema_slash_slash_host_port_path_query:
        continue;
      case s_http_url_host:
        field = UF_HOST;
        break;
      case s_http_url_host_ipv6:
        is_ipv6 = 1;
        field = UF_HOST;
        break;
      case s_http_url_host_port:
        field = UF_PORT;
        break;
      case s_http_url_path:
        field = UF_PATH;
        break;
      case s_http_url_query:
        field = UF_QUERY;
        break;
      default:
        assert(!"Unexpected state");
        return 1;
    }
    if (field == last_field) {
      u->field_data[field].len++;
    } else {
      u->field_data[field].off = (unsigned short)(p - buf);
      u->field_data[field].len = 1;
      u->field_set |= (1 << field);
      last_field = field;
    }
  }
  if ((u->field_set & (1 << 0)) && !(u->field_set & (1 << 1))) return 1;
  if ((u->field_set & (1 << 1)) && http_parse_host(buf, u, is_ipv6)) return 1;
  if (is_connect && u->field_set != (1 << 1) | (1 << 2)) return 1;
  if (u->field_set & (1 << 2)) {
    unsigned port_off = u->field_data[2].off;
    unsigned port_len = u->field_data[2].len;
    const char *q;
    unsigned long port;
    assert((unsigned)(port_off + port_len) <= buf_len && "Port number overflow");
    for (port = 0, q = buf + port_off; q < buf + port_off + port_len; q++) {
      port = port * 10 + *q - '0';
      if (port > 65535) return 1;
    }
    u->port = (unsigned short)port;
  }
  return 0;
}