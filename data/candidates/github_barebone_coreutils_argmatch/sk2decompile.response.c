static ptrdiff_t argmatch(const char *arg, const char **names, void *values,
                          size_t size) {
  ptrdiff_t i, match;
  size_t len;
  int ambiguous;
  len = strlen(arg);
  match = -1;
  ambiguous = 0;
  for (i = 0; names[i]; i++) {
    if (!strncmp(names[i], arg, len)) {
      if (strlen(names[i]) == len) return i;
      if (match == -1)
        match = i;
      else if (values &&
               !memcmp(values + match * size, values + i * size, size))
        ;
      else
        ambiguous = 1;
    }
  }
  return ambiguous ? -2 : match;
}