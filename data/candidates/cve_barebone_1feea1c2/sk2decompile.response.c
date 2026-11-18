char *build_ustar_entry_name(char *buf, const char *path, size_t path_len,
                             const char *prefix) {
  const char *end, *start, *slash1, *slash2;
  char *p;
  int has_slash = 0;
  size_t max_len = 99;
  size_t prefix_len;
  if (prefix)
    prefix_len = strlen(prefix) + 2;
  else
    prefix_len = 0;
  if (path_len < 100 && !prefix) {
    strncpy(buf, path, path_len);
    buf[path_len] = '\0';
    return buf;
  }
  end = path + path_len;
  while (1) {
    while (end > path && end[-1] == '/') {
      end--;
      has_slash = 1;
    }
    if (end <= path + 1 || end[-1] != '.' || end[-2] != '/') break;
    has_slash = 1;
    end -= 2;
  }
  if (has_slash) max_len--;
  start = end - 1;
  while (start > path && start[0] != '/') start--;
  if (start[0] == '/' && start < end - 1) start++;
  max_len -= prefix_len;
  if (end > start + max_len) end = start + max_len;
  max_len -= end - start;
  slash1 = path + 155;
  if (slash1 > start) slash1 = start;
  while (slash1 > path && slash1[0] != '/') slash1--;
  if (slash1 < start && slash1[0] == '/') slash1++;
  slash2 = slash1 + max_len;
  if (slash2 > start) slash2 = start;
  if (slash2 < slash1) slash2 = slash1;
  while (slash2 > slash1 && slash2[0] != '/') slash2--;
  if (slash2 < start && slash2[0] == '/') slash2++;
  p = buf;
  if (slash1 > path) {
    strncpy(p, path, slash1 - path);
    p += slash1 - path;
  }
  if (slash2 > slash1) {
    strncpy(p, slash1, slash2 - slash1);
    p += slash2 - slash1;
  }
  if (prefix) {
    strcpy(p, prefix);
    p += strlen(prefix);
    *p++ = '/';
  }
  strncpy(p, start, end - start);
  p += end - start;
  if (has_slash) *p++ = '/';
  *p = '\0';
  return buf;
}