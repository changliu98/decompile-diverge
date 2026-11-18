void basename_discriminant(const char *path, unsigned long *hash,
                           unsigned long *len) {
  const char *p;
  p = strrchr(path, '/');
  if (p)
    p++;
  else
    p = path;
  *len = 0;
  *hash = 0;
  while (*p) {
    *hash *= 33;
    *hash += *p++;
    (*len)++;
  }
}