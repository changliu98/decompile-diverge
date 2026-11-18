int sdscmp(const sds s1, const sds s2) {
  size_t l1, l2, minlen;
  int cmp;
  l1 = sdslen(s1);
  l2 = sdslen(s2);
  minlen = (l1 < l2) ? l1 : l2;
  cmp = memcmp(s1, s2, minlen);
  if (cmp != 0) return cmp;
  if (l1 > l2) return 1;
  if (l1 < l2) return -1;
  return 0;
}