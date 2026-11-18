/* WARNING: Removing unreachable block (ram,0x00109727) */

int http_parser_parse_url(char *buf,size_t buflen,int is_connect,http_parser_url *u)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  unsigned_long v;
  char *end;
  char *p_1;
  uint16_t len;
  uint16_t off;
  int found_at;
  http_parser_url_fields old_uf;
  http_parser_url_fields uf;
  char *p;
  state s;
  http_parser_url *u_local;
  int is_connect_local;
  size_t buflen_local;
  char *buf_local;
  int local_c;
  
  found_at = 0;
  if (buflen == 0) {
    local_c = 1;
  }
  else {
    u->field_set = 0;
    u->port = 0;
    s = s_req_spaces_before_url;
    if (is_connect != 0) {
      s = s_req_server_start;
    }
    old_uf = UF_MAX;
    for (p = buf; p < buf + buflen; p = p + 1) {
      s = parse_url_char(s,*p);
      switch(s) {
      case s_dead:
        return 1;
      default:
                    /* WARNING: Subroutine does not return */
        __assert_fail("!\"Unexpected state\"","./func.c",0x9b0,
                      "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)"
                     );
      case s_req_schema:
        uf = UF_SCHEMA;
        break;
      case s_req_schema_slash:
      case s_req_schema_slash_slash:
      case s_req_server_start:
      case s_req_query_string_start:
      case s_req_fragment_start:
        goto LAB_0010961a;
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
      }
      if (uf == old_uf) {
        u->field_data[uf].len = u->field_data[uf].len + 1;
      }
      else {
        u->field_data[uf].off = (short)p - (short)buf;
        u->field_data[uf].len = 1;
        u->field_set = u->field_set | (ushort)(1 << (sbyte)uf);
        old_uf = uf;
      }
LAB_0010961a:
    }
    if (((u->field_set & 1) == 0) || ((u->field_set & 2) != 0)) {
      if (((u->field_set & 2) == 0) || (iVar3 = http_parse_host(buf,u,found_at), iVar3 == 0)) {
        if ((is_connect == 0) || (u->field_set == 6)) {
          if ((u->field_set & 4) != 0) {
            uVar1 = u->field_data[2].off;
            uVar2 = u->field_data[2].len;
            if (buflen < (ulong)(long)(int)((uint)uVar1 + (uint)uVar2)) {
                    /* WARNING: Subroutine does not return */
              __assert_fail("(size_t) (off + len) <= buflen && \"Port number overflow\"","./func.c",
                            0x9df,
                            "int http_parser_parse_url(const char *, size_t, int, struct http_parser_url *)"
                           );
            }
            v = 0;
            for (p_1 = buf + (int)(uint)uVar1;
                p_1 < buf + (long)(int)(uint)uVar2 + (long)(int)(uint)uVar1; p_1 = p_1 + 1) {
              v = (long)(*p_1 + -0x30) + v * 10;
              if (0xffff < v) {
                return 1;
              }
            }
            u->port = (uint16_t)v;
          }
          local_c = 0;
        }
        else {
          local_c = 1;
        }
      }
      else {
        local_c = 1;
      }
    }
    else {
      local_c = 1;
    }
  }
  return local_c;
}