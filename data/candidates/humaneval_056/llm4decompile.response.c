int func0(const char *brackets) {
  int i = 0;
  int level = 0;
  while (brackets[i] != '\0') {
    if (brackets[i] == '<') {
      level++;
    }
    if (brackets[i] == '>') {
      level--;
    }
    if (level < 0) {
      return 0;
    }
    i++;
  }
  return level == 0;
}