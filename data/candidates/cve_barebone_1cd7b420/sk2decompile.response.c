static CK_RV get_name_len(int depth, const unsigned char *start,
                          const unsigned char *name, const unsigned char *end,
                          int *name_len, int *total_len) {
  const unsigned char *p;
  int len;
  int dummy;
  CK_RV rc;
  if (depth > 10) return 0x50003;
  *name_len = 0;
  *total_len = 0;
  p = name;
  while (*p) {
    if ((*p & 0xc0) == 0xc0) {
      int i;
      unsigned short offset;
      len = 0;
      pj_memcpy(&offset, p, 2);
      offset ^= foldCase(0xc000);
      offset = foldCase(offset);
      if (offset >= end - start) return 0x50003;
      rc = get_name_len(depth + 1, start, start + offset, end, &dummy, &len);
      if (rc) return rc;
      *name_len += 2;
      *total_len += len;
      return 0;
    }
    len = *p;
    if (start + len > end) return 0x50003;
    p += len + 1;
    *name_len += len + 1;
    if (*p) len++;
    *total_len += len;
    if (p >= end) return 0x50001;
  }
  p++;
  *name_len += 1;
  return 0;
}