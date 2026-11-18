int func0(char *str) {
  int ret = 0;
  if (strlen(str) > 0) {
    if (str[0] >= 'A' && str[0] <= 'Z') {
      ret = 1;
    }
  }
  return ret;
}