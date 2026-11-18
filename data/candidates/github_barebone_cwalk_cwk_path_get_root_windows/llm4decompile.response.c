void cwk_path_get_root_windows(const char *path, size_t *length)
{
  *length = 0;





  if (path[0] == '\0') {
    return;
  }

  if (cwk_path_is_separator(path)) {
    if (cwk_path_is_separator(path + 1)) {
      const char *start = path;
      path += 2;





      if (path[0] == '?' || path[0] == '.') {
        path++;
        if (cwk_path_is_separator(path)) {
          *length = path - start;
          return;
        }
      }

      path = cwk_path_find_next_stop(path);
      while (cwk_path_is_separator(path)) {
        path++;
      }
      path = cwk_path_find_next_stop(path);
      if (cwk_path_is_separator(path)) {
        path++;
      }
      *length = path - start;
    } else {
      (*length)++;
    }
  } else if (path[1] == ':') {
    *length = 2;
    if (cwk_path_is_separator(path + 2)) {
      (*length)++;
    }
  }
}