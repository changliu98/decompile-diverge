char *truncate_string_at_char(char *str, char c) {
  char *p;
  for (p = str; *p != '\0'; p++) {
    if (*p == c) {
      *p = '\0';
    }
  }
  return str;
}