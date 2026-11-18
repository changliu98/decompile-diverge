sds sdsmapchars(sds s, const char *from, const char *to, size_t setsize) {
  size_t j, i, len = sdslen(s);
  for (i = 0; i < len; i++) {
    for (j = 0; j < setsize; j++) {
      if (s[i] == from[j]) {
        s[i] = to[j];
        break;
      }
    }
  }
  return s;
}