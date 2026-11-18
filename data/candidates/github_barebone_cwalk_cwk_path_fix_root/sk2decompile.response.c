void cwk_path_fix_root(char *path, size_t path_size, size_t root_size) {
  size_t i;
  if (cwk_path_is_absolute) {
    return;
  }
  if (root_size > path_size) {
    root_size = path_size;
  }
  for (i = 0; i < root_size; ++i) {
    if (cwk_path_is_separator(&path[i])) {
      path[i] = cwk_path_separator[0];
    }
  }
}