int __cdecl http_parser_parse_url(const char *buf, size_t buflen, int is_connect, http_parser_url *u)
{
  http_parser_url_fields old_uf = http_parser_url_fields::UF_MAX;
  http_parser_url_fields uf;
  state s;
  const char *p;
  const char *p_0;
  int found_at = 0;
  uint16_t off, len;
  uint64_t port_val = 0;

  if (buflen == 0)
    return 1;

  u->field_set = 0;
  u->port = 0;

  // Set initial state based on whether this is a CONNECT request
  s = is_connect ? state::s_req_host_start : state::s_req_schema;

  for (p = buf; p < buf + buflen; ++p)
  {
    s = parse_url_char(s, *p);

    switch (s)
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

      case state::s_req_server_with_at:
        found_at = 1;
        // fallthrough
        
      case state::s_req_server:
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
        __assert_fail("!(\"Unexpected state\")", "./func.c", 0x9B0u, 
                      "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)");
    }

    if (uf == old_uf)
    {
      u->field_data[uf].len++;
    }
    else
    {
      u->field_data[uf].off = (uint16_t)(p - buf);
      u->field_data[uf].len = 1;
      u->field_set |= (1 << uf);
      old_uf = uf;
    }
  }

  // Validate schema and host presence
  if ((u->field_set & 1) != 0 && (u->field_set & 2) == 0)
    return 1; // Schema present but host missing

  if ((u->field_set & 2) != 0 && http_parse_host(buf, u, found_at))
    return 1; // Host parsing failed

  // CONNECT requests must only have host and port
  if (is_connect && u->field_set != 6)
    return 1;

  // Parse port number if present
  if ((u->field_set & 4) != 0)
  {
    off = u->field_data[http_parser_url_fields::UF_PORT].off;
    len = u->field_data[http_parser_url_fields::UF_PORT].len;

    if ((size_t)off + len > buflen)
    {
      __assert_fail("(size_t) (off + len) <= buflen && \"Port number overflow\"", "./func.c", 0x9DFu, 
                    "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)");
    }

    port_val = 0;
    for (p_0 = buf + off; p_0 < buf + off + len; ++p_0)
    {
      port_val = port_val * 10 + (*p_0 - '0');
      if (port_val > 0xFFFF)
        return 1;
    }
    u->port = port_val;
  }

  return 0;
}