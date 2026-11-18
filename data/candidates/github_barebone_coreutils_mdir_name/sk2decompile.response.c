char *mdir_name(const char *path) {
  size_t len = dir_len(path);
  char *dir = malloc(len + 1 + (len == 0));
  if (!dir) return NULL;
  memcpy(dir, path, len);
  if (len == 0) {
    len = 1;
    dir[0] = '.';
  }
  dir[len] = '\0';
  return dir;
}