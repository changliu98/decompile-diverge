int _count_valid_chars(char *str) {
  int i, count = 0;
  for (i = 0; i < strlen(str); i++) {
    if (strchr("2357BD", str[i])) {
      count++;
    }
  }
  return count;
}