int _strlen_sum(char *str) {
  int len;
  len = strlen(str);
  return len * (len + 1) / 2;
}