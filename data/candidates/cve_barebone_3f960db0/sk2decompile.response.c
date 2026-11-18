char *gf_text_get_utf8_line(char *line, gf_long line_size, gf_file *f,
                            gf_long mode) {
  char *ret;
  char tmp[2048];
  unsigned int j, len, i;
  unsigned char c;
  memset(line, 0, line_size);
  ret = gf_fgets(line, line_size, f);
  if (ret == NULL) return NULL;
  if (mode == 0 || mode == 1) {
    j = 0;
    len = strlen(line);
    for (i = 0; i < len; i++) {
      if (mode == 0) {
        if ((line[i] & 0x80) != 0) {
          if ((line[i + 1] & 0xc0) == 0x80) {
            if ((line[i] & 0xe0) == 0xc0) {
              tmp[j] = line[i];
              j++;
              i++;
            } else if ((line[i] & 0xf0) == 0xe0) {
              tmp[j] = line[i];
              j++;
              i++;
              tmp[j] = line[i];
              j++;
              i++;
            } else if ((line[i] & 0xf8) == 0xf0) {
              tmp[j] = line[i];
              j++;
              i++;
              tmp[j] = line[i];
              j++;
              i++;
              tmp[j] = line[i];
              j++;
              i++;
            } else {
              i++;
              continue;
            }
          } else {
            tmp[j] = (line[i] & 0x1f) >> 2 | 0xc0;
            j++;
            line[i] &= 0x7f;
          }
        }
      }
      tmp[j] = line[i];
      j++;
      if (j >= 2048 - 1) {
        tmp[j] = '\0';
        strcpy(line, tmp);
        return ret;
      }
    }
    tmp[j] = '\0';
    strcpy(line, tmp);
    return ret;
  } else if (mode == 2) {
    for (i = 0; line[i] != 0 || line[i + 1] != 0; i += 2) {
      c = line[i + 1];
      line[i + 1] = line[i];
      line[i] = c;
    }
    unsigned short *s = (unsigned short *)line;
    i = gf_utf8_wcstombs(tmp, 2048, &s);
    if (i == -1) i = 0;
    tmp[i] = '\0';
    strcpy(line, tmp);
    if (mode == 3) gf_fgetc(f);
    return ret;
  }
  return ret;
}