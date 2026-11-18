void path_to_uri(char *path, unsigned long path_size, unsigned long path_len)
{
  unsigned long i;
  if (path_style == URI_PATH) {
    if (path_len > path_size)
      path_len = path_size;
    for (i = 0; i < path_len; i++)
      if (is_uri_separator(&path[i]))
        path[i] = separators[0];
  }
}