char *emit_literal(char *p, const char *lit, int len, bool is_64) {
  int n = len - 1;
  if (n < 60) {
    *p++ = 4 * n;
    if (is_64 && len <= 16) {
      unaligned_copy64(lit, p);
      unaligned_copy64(lit + 8, p + 8);
    } else {
      memcpy(p, lit, len);
      p += len;
    }
  } else {
    int count = 0;
    *p++ = 0;
    while (n > 0) {
      *p++ = n;
      n >>= 8;
      count++;
    }
    do {
      if (!(!(count >= 1))) {
        __assert_fail("!(!(count >= 1))", "func.c", 583U,
                      "char *emit_literal(char *, const char *, int, _Bool)");
      }
    } while (0);
    do {
      if (!(!(count <= 4))) {
        __assert_fail("!(!(count <= 4))", "func.c", 584U,
                      "char *emit_literal(char *, const char *, int, _Bool)");
      }
    } while (0);
    *p++ = 4 * (59 + count);
    memcpy(p, lit, len);
    p += len;
  }
  return p;
}