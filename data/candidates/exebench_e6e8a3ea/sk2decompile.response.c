int last_slash(char *path, int *slash_count, int *path_len) {
  int slash_cnt = 0;
  int last_slash_pos = 0;
  int i;
  for (i = 0; path[i] != '\0' && i < 256; i++) {
    if (path[i] == '/') {
      slash_cnt++;
      last_slash_pos = i;
    }
  }
  *slash_count = slash_cnt;
  *path_len = i;
  return last_slash_pos;
}