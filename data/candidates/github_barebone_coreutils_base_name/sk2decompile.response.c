char *base_name(const char *path) {
  const char *base;
  char *result;
  size_t len;
  base = last_component(path);
  if (*base == '\0') {
    base = path;
    len = base_len(base);
  } else {
    len = base_len(base);
    if (base[len] == '/') len++;
  }
  result = ximalloc(len + 1);
  memcpy(result, base, len);
  result[len] = '\0';
  return result;
}