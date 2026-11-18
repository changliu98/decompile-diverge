bool
strip_trailing_slashes (char *file)
{
  char *base = last_component (file);

  /* last_component returns "" for file system roots, but we need to turn
     "///" into "/".  */
  if (! *base)
    base = file;
  char *base_lim = base + base_len (base);
  bool had_slash = (*base_lim != '\0');
  *base_lim = '\0';
  return had_slash;
}