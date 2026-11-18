static const char *last_component(const char *path) {
  const char *p;
  int slash;
  while (*path == '/') path++;
  slash = 0;
  for (p = path; *p; p++) {
    if (*p == '/')
      slash = 1;
    else if (slash) {
      path = p;
      slash = 0;
    }
  }
  return path;
}