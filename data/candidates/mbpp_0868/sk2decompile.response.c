int func0(char *str) {
  int i, count = 0;
  while (*str == ' ') str++;
  for (i = 0; i < strlen(str); i++) {
    if (str[i] != ' ')
      count++;
    else
      count = 0;
  }
  return count;
}