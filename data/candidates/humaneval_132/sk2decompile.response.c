int _is_invalid(char *s) {
  int i, level = 0, max_level = 0;
  for (i = 0; i < strlen(s); i++) {
    if (s[i] == '[') level++;
    if (s[i] == ']') level--;
    if (level < 0) level = 0;
    if (level > max_level) max_level = level;
    if (level <= max_level - 2) return 1;
  }
  return 0;
}