int _is_valid_suffix(const char *name) {
  int len = strlen(name);
  if (len == 0) return 0;
  unsigned char last = name[len - 1];
  if (!isalpha(last)) return 0;
  if (len == 1) return 1;
  unsigned char second_last = name[len - 2];
  if (!isalpha(second_last)) return 0;
  return 1;
}