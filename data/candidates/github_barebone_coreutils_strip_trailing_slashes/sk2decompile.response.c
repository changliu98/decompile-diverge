int strip_trailing_slashes(char *path) {
  char *last = last_component(path);
  char *end;
  int ret;
  if (!*last) last = path;
  end = last + base_len(last);
  ret = *end != '\0';
  *end = '\0';
  return ret;
}