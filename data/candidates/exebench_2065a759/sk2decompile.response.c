int set_filename(char *filename, char *path) {
  while (*path) {
    if (*path == '/') {
      *filename = '\0';
      return 2;
    }
    *filename = *path;
    filename++;
    path++;
  }
  *filename = '\0';
  return 1;
}