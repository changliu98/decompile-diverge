static int strip_trailing_slashes(char *path)
{
  char *base = last_component(path);
  if (!*base)
    base = path;
  char *end = base + base_len(base);
  int had_slash = *end != '\0';
  *end = '\0';
  return had_slash;
}