int func0(char *str) {
  int i, len, count, max;
  count = 0;
  max = 0;
  len = strlen(str);
  for (i = 0; i < len; i++) {
    if (isalpha(str[i])) {
      count++;
    } else {
      if (count > max) {
        max = count;
      }
      count = 0;
    }
  }
  if (isalpha(str[len - 1]) && count > max) {
    max = count;
  }
  return max;
}