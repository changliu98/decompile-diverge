static CK_RV get_name_len(int depth, const unsigned char *start,
                          const unsigned char *name, const unsigned char *end,
                          int *name_len, int *utf8_len) {
  const unsigned char *p;
  int len;
  CK_RV rc;
  if (depth > 10) return 0x50003;
  if (name >= end) return 0x50003;
  *name_len = 0;
  *utf8_len = 0;
  p = name;
  while (1) {
    if (*p == 0) {
      p++;
      (*name_len)++;
      return 0;
    }
    if ((*p & 0xc0) == 0xc0) {
      int utf8_len_tmp;
      unsigned short offset;
      utf8_len_tmp = 0;
      pj_memcpy(&offset, p, 2);
      offset ^= foldCase(0xc000);
      offset = foldCase(offset);
      if (offset >= end - start) return 0x50003;
      rc = get_name_len(depth + 1, start, start + offset, end, &len,
                        &utf8_len_tmp);
      if (rc) return rc;
      *name_len += 2;
      *utf8_len += utf8_len_tmp;
      return 0;
    }
    len = *p;
    if (p + len + 2 > end) return 0x50003;
    p += len + 1;
    *name_len += len + 1;
    if (*p) len++;
    *utf8_len += len;
  }
}