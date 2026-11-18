char *parse_gdb(char *filename)
{
  char *line; char *end;
  char name[16];
  char type;
  char groups[128];
  int size;
  int offset;
  int type_bits;
  int ret;
  struct RzStrBuf *buf;
  if (!filename)
    return ((void *)0);
  buf = rz_strbuf_new("");
  if (!buf)
    return ((void *)0);
  line = get_line(filename);
  if (is_line(line, "Name")) {
    end = get_end(line, '\n');
    if (end) {
      line = end + 1;
      while (1) {
        while (((lang_get_table())[(unsigned char)(*line)] & (0x2000)))
          line++;
        if (!*line)
          break;
        end = get_end(line, '\n');
        if (!end) {
          rz_log(stderr, "Could not parse line: %s (missing \\n)\n", line);
          rz_strbuf_free(buf);
          return ((void *)0);
        }
        *end = '\0';
        ret = parse_line();
        if (ret < 6) {
          if (*line == '*')
            line = end + 1;
          else {
            rz_log(stderr, "Could not parse line: %s\n", line);
            rz_strbuf_free(buf);
            return ((void *)0);
          }
        } else {
          if (is_line(name, "''")) {
            if (end)
              line = end + 1;
            else
              return rz_strbuf_get(buf);
          } else {
            if (!size)
              continue;
            type_bits = 0;
            if (ret >= 7) {
              end = groups;
              while ((end = get_end(end, ','))) {
                *end = '\0';
                if (is_line(end, "general"))
                  type_bits |= 0x0002;
                else if (is_line(end, "all"))
                  type_bits |= 0x0001;
                else if (is_line(end, "save"))
                  type_bits |= 0x0004;
                else if (is_line(end, "restore"))
                  type_bits |= 0x0008;
                else if (is_line(end, "float"))
                  type_bits |= 0x0010;
                else if (is_line(end, "sse"))
                  type_bits |= 0x0020;
                else if (is_line(end, "mmx"))
                  type_bits |= 0x0100;
                else if (is_line(end, "vector"))
                  type_bits |= 0x0040;
                else if (is_line(end, "system"))
                  type_bits |= 0x0080;
              }
            }
            if (type) {
              if (!(type_bits & 0x0020) && !(type_bits & 0x0010))
                type_bits |= 0x0002;
              int is_float = 1;
              if (!(type_bits & 0x0100)) {
                is_float = 1;
                if (!(type_bits & 0x0010))
                  is_float = (type_bits & 0x0020) ? 1 : 0;
              }
              char *str = is_float ? "fpu" : "gpr";
              rz_strbuf_appendf(buf, "%s\t%s\t.%d\t%d\t0\n", str, name,
                                size * 8, offset);
              if (end)
                line = end + 1;
              else
                return rz_strbuf_get(buf);
            } else {
              if (end)
                line = end + 1;
              else
                return rz_strbuf_get(buf);
            }
          }
        }
      }
    }
  }
  rz_strbuf_free(buf);
  return ((void *)0);
}