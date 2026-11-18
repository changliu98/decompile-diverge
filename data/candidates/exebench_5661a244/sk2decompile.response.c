unsigned FAT_parse_directory(const unsigned char *dir, unsigned dir_len,
                             unsigned *start, unsigned *end) {
  while (*start < dir_len && dir[*start] != '\\') (*start)++;
  if (*start == dir_len) return 0;
  (*start)++;
  *end = *start + 1;
  while (*end < dir_len && dir[*end] != '\\') (*end)++;
  return *end - *start;
}