int func0(const char *string, char c) {
  int flag = -1;
  int length = strlen(string);
  for (int i = 0; i < length; i++) {
    if (string[i] == c) {
      flag = i;
    }
  }
  if (flag == -1) {
    return -1;
  } else {
    return flag + 1;
  }
}