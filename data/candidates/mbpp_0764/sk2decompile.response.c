int func0(char *str) {
  int i, count = 0;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      count++;
    }
  }
  return count;
}