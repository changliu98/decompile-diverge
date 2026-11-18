int func0(char *str) {
  int i, count = 0;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      count++;
    }
  }
  return count;
}