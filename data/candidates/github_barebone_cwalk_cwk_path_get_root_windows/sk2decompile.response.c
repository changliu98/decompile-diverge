void cwk_path_get_root_windows(const char *path, size_t *root_length) {
  const char *p;
  *root_length = 0;
  if (path[0] == '\0') {
    return;
  }
  if (cwk_path_is_separator(path)) {
    if (cwk_path_is_separator(path + 1)) {
      p = path + 2;
      if (*p == '?' || *p == '.') {
        p++;
        if (cwk_path_is_separator(p)) {
          p++;
        }
      }
      if (cwk_path_is_separator(p)) {
        *root_length = 4;
      } else {
        p = cwk_path_find_next_stop(p);
        while (cwk_path_is_separator(p)) {
          p++;
        }
        p = cwk_path_find_next_stop(p);
        if (cwk_path_is_separator(p)) {
          p++;
        }
        *root_length = p - path;
      }
    } else {
      *root_length = 1;
    }
  } else if (path[1] == ':') {
    *root_length = 2;
    if (cwk_path_is_separator(path + 2)) {
      *root_length = 3;
    }
  }
}