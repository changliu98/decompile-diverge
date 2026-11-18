int
http_parser_parse_url(const char *buf, size_t buflen, int is_connect,
                      struct http_parser_url *u)
{
  enum state s;
  const char *p;
  enum http_parser_url_fields uf, old_uf;
  int found_at = 0;

  if (buflen == 0) {
    return 1;
  }

  u->port = u->field_set = 0;
  s = is_connect ? s_req_server_start : s_req_spaces_before_url;
  uf = old_uf = UF_MAX;

  for (p = buf; p < buf + buflen; p++) {
    s = parse_url_char(s, *p);





    switch (s) {
      case s_dead:
        return 1;


      case s_req_schema:
        uf = UF_SCHEMA;
        break;

      case s_req_schema_slash:
      case s_req_schema_slash_slash:
      case s_req_server_start:
      case s_req_query_string_start:
      case s_req_fragment_start:
        continue;

      case s_req_server_with_at:
        found_at = 1;


      case s_req_server:
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
        __assert_fail("!\"Unexpected state\"", "./func.c", 2480, "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)");
    }


    if (uf == old_uf) {
      u->field_data[uf].len++;
      continue;
    }

    u->field_data[uf].off = p - buf;
    u->field_data[uf].len = 1;

    u->field_set |= (1 << uf);
    old_uf = uf;
  }







  if ((u->field_set & (1 << UF_SCHEMA)) != 0) {
    if ((u->field_set & (1 << UF_HOST)) == 0) {
      return 1;
    }
  }


  if ((u->field_set & (1 << UF_HOST)) != 0) {
    if (http_parse_host(buf, u, found_at) != 0) {
      return 1;
    }
  }


  if (is_connect && u->field_set != ((1 << UF_HOST)|(1 << UF_PORT))) {
    return 1;
  }

  if ((u->field_set & (1 << UF_PORT)) != 0) {

    unsigned short port = 0;
    unsigned short off = u->field_data[UF_PORT].off;
    unsigned short len = u->field_data[UF_PORT].len;
    const char *p = buf + off;
    unsigned long v = 0;

    do { if (!(size_t) (off + len) <= buflen && "Port number overflow") __assert_fail("(size_t) (off + len) <= buflen && \"Port number overflow\"", "./func.c", 2527, "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)"); } while(0);

    for (; p < buf + off + len; p++) {
      v *= 10;
      v += *p - '0';

      if (v > 0xffff) {

        return 1;
      }
    }

    port = (unsigned short) v;
    u->port = port;
  }

  return 0;
}