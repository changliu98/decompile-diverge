static int base_len(const char *path) {
  unsigned int len;
  len = strlen(path);
  while (len > 1 && path[len - 1] == '/') len--;
  return len;
}