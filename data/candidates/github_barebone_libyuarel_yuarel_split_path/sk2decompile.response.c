int yuarel_split_path(char *path, char **parts, int max_parts) {
  char *p = path;
  int i = 0;
  if (path == NULL || *path == '\0') return -1;
  while (1) {
    while (*p == '/') p++;
    if (*p == '\0') break;
    parts[i++] = p;
    p = strchr(p, '/');
    if (p == NULL) break;
    *p++ = '\0';
    if (i >= max_parts) break;
  }
  return i;
}