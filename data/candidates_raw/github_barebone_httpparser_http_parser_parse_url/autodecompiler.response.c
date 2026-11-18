int http_parser_parse_url(const char *url, size_t buflen, int is_connect, struct http_parser_url *u)
{
  int state;
  unsigned short port_off, len;
  char *p;
  int found_at = 0;

  if (buflen == 0)
  {
    state = (1);
    goto _out;
  }

  u->field_set = 0;
  u->port = 0;

  state = (is_connect ? (24) : (20));
  int old_uf = 7;
  p = (char *) url;

  while (p < url + buflen)
  {
    state = parse_url_char(state, *p);

    switch (state)
    {
      case (1):
        state = (1);
        goto _out;

      case (22):
      case (23):
      case (24):
      case (28):
      case (30):
        goto _out;

      case (21):
        uf = (0);
        break;

      case (26):
        found_at = 1;

      case (25):
        uf = (1);
        break;

      case (27):
        uf = (3);
        break;

      case (29):
        uf = (4);
        break;

      case (31):
        uf = (5);
        break;

      default:
        do { ___assert_fail("!\"Unexpected state\"", "./func.c", 2480, "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *"); } while (0);
    }

    if (uf != old_uf)
    {
      u->field_data[uf].off = (unsigned short) (p - url);
      u->field_data[uf].len = 1;
      u->field_set |= (1 << uf);
      old_uf = uf;
    }
    else
    {
      u->field_data[uf].len++;
    }

    ++p;
  }

  if ((u->field_set & (1 << 0)) && !(u->field_set & (1 << 1)))
  {

    state = (1);
    goto _out;
  }

  if ((u->field_set & (1 << 1)) && http_parse_host(url, u, found_at))
  {

    state = (1);
    goto _out;
  }

  if (is_connect && u->field_set != ((1 << 1) | (1 << 2)))
  {

    state = (1);
    goto _out;
  }

  if ((u->field_set & (1 << 2)))
  {
    size_t off = u->field_data[(2)].off;
    size_t len = u->field_data[(2)].len;
    char *buf = (char *) url + off + len;


    do { ((size_t) (off + len) <= buflen && "Port number overflow") ? (void) 0 : ___assert_fail("(size_t) (off + len) <= buflen && \"Port number overflow\"", "./func.c", 2527, "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *"); } while (0);

    unsigned long v = 0;
    char *ch = (char *) url + off;

    while (ch < buf)
    {
      v *= 10;
      v += *ch - '0';

      if (v > 0xffff)
      {
        state = (1);
        goto _out;
      }

      ++ch;
    }

    u->port = (unsigned short) v;
  }

  state = (0);

_out:
  return state;
}