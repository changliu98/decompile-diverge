void garray_put_str(struct garray *ga, char *str)
{
  char buf[65];
  char *s;
  char *p;
  int c; int clen;
  int same_len;
  int same;
  struct garray *ga2 = ga;
  if (str == ((void *)0)) {
    garray_put(ga2, (unsigned char *)"NULL");
  } else {
    for (p = str; *p != '\0'; p++) {
      same_len = 1;
      s = p;
      c = garray_get_char(&s);
      for (clen = s - p; ; s += clen) {
        same = 0;
        if (*s != '\0') {
          int c2 = mb_ptr2char((unsigned char *) s);
          same = c == c2;
        }
        if (!same) {
          break;
        }
        same_len++;
      }
      if (same_len > 20) {
        garray_put(ga2, (unsigned char *)"\\[");
        garray_put(ga2, p, clen);
        garray_put(ga2, (unsigned char *)" occurs ");
        int2str(buf, sizeof(buf), "%d", same_len);
        garray_put(ga2, (unsigned char *)buf);
        garray_put(ga2, (unsigned char *)" times]");
        p = s - 1;
      } else {
        garray_put(ga2, p, clen);
      }
    }
  }
}