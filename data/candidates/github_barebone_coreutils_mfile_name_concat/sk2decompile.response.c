char *mfile_name_concat(const char *dir, const char *file, char **file_ptr) {
  const char *last = last_component(dir);
  size_t last_len = base_len(last);
  size_t dir_len = last - dir + last_len;
  size_t file_len = strlen(file);
  char sep = 0;
  char *result;
  char *file_start;
  if (last_len == 0) {
    if (file[0] == '/') sep = '.';
  } else if (last[last_len - 1] != '/' && file[0] != '/') {
    sep = '/';
  }
  result = malloc(dir_len + (sep ? 1 : 0) + file_len + 1);
  if (!result) return NULL;
  memcpy(result, dir, dir_len);
  result[dir_len] = sep;
  file_start = result + dir_len + (sep ? 1 : 0);
  if (file_ptr) *file_ptr = file_start;
  memcpy(file_start, file, file_len);
  file_start[file_len] = 0;
  return result;
}