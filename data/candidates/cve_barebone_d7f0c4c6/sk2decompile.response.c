char *gf_text_get_utf8_line(char *line, gf_long len, gf_file *f,
                            gf_long encoding) {
  char tmp[2048];
  char *ret;
  unsigned i, l;
  unsigned short *p;
  char c;
  memset(line, 0, len);
  ret = gf_fgets(line, len, f);
  if (ret == NULL) return NULL;
  if (encoding == 0 || encoding == 1) {
    i = 0;
    l = strlen(line);
    for (i = 0; i < l; i++) {
      if (encoding == 0) {
        if ((line[i] & 0x80) != 0) {
          if ((line[i + 1] & 0xc0) == 0x80) {
            if ((line[i] & 0xe0) == 0xc0) {
              if (i + 1 < 2048) {
                tmp[i] = line[i];
                i++;
              }
            } else if ((line[i] & 0xf0) == 0xe0) {
              if (i + 2 < 2048) {
                tmp[i] = line[i];
                i++;
                tmp[i] = line[i];
                i++;
                tmp[i] = line[i];
                i++;
              }
            } else if ((line[i] & 0xf8) == 0xf0) {
              if (i + 3 < 2048) {
                tmp[i] = line[i];
                i++;
                tmp[i] = line[i];
                i++;
                tmp[i] = line[i];
                i++;
                tmp[i] = line[i];
                i++;
              }
            } else {
              i++;
              continue;
            }
          } else {
            if (i + 1 < 2048) {
              tmp[i] = (line[i] & 0x3f) | 0xc0;
              i++;
              line[i - 1] &= 0x7f;
            }
          }
        }
      }
      if (i + 1 < 2048) {
        tmp[i] = line[i];
        i++;
      }
    }
    if (i >= 2048) i = 2048 - 1;
    tmp[i] = 0;
    strcpy(line, tmp);
    return ret;
  }
  if (encoding == 2) {
    for (i = 0; line[i] != 0 || line[i + 1] != 0; i += 2) {
      c = line[i + 1];
      line[i + 1] = line[i];
      line[i] = c;
    }
  }
  p = (unsigned short *)line;
  i = gf_utf8_wcstombs(tmp, 2048, &p);
  if (i == -1) i = 0;
  tmp[i] = 0;
  strcpy(line, tmp);
  if (encoding == 3) gf_fgetc(f);
  return ret;
}