int func0(char *str) {
  int i, len, count = 0;
  len = strlen(str);
  for (i = 0; i < len; i++) {
    if (i == str[i] - 65 || i == str[i] - 97) count++;
  }
  return count;
}