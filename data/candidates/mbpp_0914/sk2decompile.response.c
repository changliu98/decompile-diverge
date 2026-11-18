bool func0(char *str) {
  int len = strlen(str);
  for (int i = 0; i < len - 2; i++) {
    if (str[i] != str[i + 2]) {
      return false;
    }
  }
  if (str[0] == str[1]) {
    return false;
  }
  return true;
}