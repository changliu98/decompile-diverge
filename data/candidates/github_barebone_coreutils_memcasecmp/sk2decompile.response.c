int memcasecmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;
  size_t i;
  int diff;
  for (i = 0; i < n; i++) {
    unsigned char c2 = p2[i];
    diff = toupper(p1[i]) - toupper(c2);
    if (diff) return diff;
  }
  return 0;
}