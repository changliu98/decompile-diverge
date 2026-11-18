char *gdb_to_rz_profile(const char *gdb_profile) {
  if (!gdb_profile) {
    return NULL;
  }
  RStrBuf *buf = rz_strbuf_new("");
  if (!buf) {
    return NULL;
  }
  char *line = rz_str_trim_head_ro(gdb_profile);
  if (rz_str_startswith(line, "Name")) {
    line = strchr(line, '\n');
    if (!line) {
      rz_strbuf_free(buf);
      return NULL;
    }
    line++;
  }
  while (1) {
    while (isspace((unsigned char)*line)) {
      line++;
    }
    if (*line == '\0') {
      break;
    }
    char *end = strchr(line, '\n');
    if (!end) {
      fprintf(stderr, "Could not parse line: %s (missing \\n)\n", line);
      rz_strbuf_free(buf);
      return NULL;
    }
    *end = '\0';
    int n, a, b, c, d;
    char e[128], f[16];
    n = sscanf(line, "%d %d %d %d %d %15s", &a, &b, &c, &d, &e, f);
    if (n < 6) {
      if (*line == '*') {
        line = end + 1;
        continue;
      }
      fprintf(stderr, "Could not parse line: %s\n", line);
      rz_strbuf_free(buf);
      return NULL;
    }
    if (rz_str_startswith(f, "''")) {
      line = end + 1;
      continue;
    }
    if (c == 0) {
      line = end + 1;
      continue;
    }
    int flags = 0;
    if (n >= 7) {
      char *p = e;
      while (1) {
        char *q = strchr(p, ',');
        if (q) {
          *q = '\0';
        }
        if (rz_str_startswith(p, "general")) {
          flags |= 2;
        } else if (rz_str_startswith(p, "all")) {
          flags |= 1;
        } else if (rz_str_startswith(p, "save")) {
          flags |= 4;
        } else if (rz_str_startswith(p, "restore")) {
          flags |= 8;
        } else if (rz_str_startswith(p, "float")) {
          flags |= 16;
        } else if (rz_str_startswith(p, "sse")) {
          flags |= 32;
        } else if (rz_str_startswith(p, "mmx")) {
          flags |= 256;
        } else if (rz_str_startswith(p, "vector")) {
          flags |= 64;
        } else if (rz_str_startswith(p, "system")) {
          flags |= 128;
        }
        if (!q) {
          break;
        }
        p = q + 1;
      }
    }
    if (d) {
      if (!(flags & 32) && !(flags & 16)) {
        flags |= 2;
      }
      rz_strbuf_appendf(buf, "%s\t%s\t.%d\t%d\t0\n",
                        (flags & 256) || (flags & 16) || (flags & 32) ? "gpr"
                                                                      : "fpu",
                        f, c * 8, d);
    }
    line = end + 1;
  }
  return rz_strbuf_drain(buf);
}