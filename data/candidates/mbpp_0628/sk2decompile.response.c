char *func0(char *str) {
  char *p = str;
  int space_num = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (p[i] == ' ') {
      space_num++;
    }
  }
  int new_len = len + space_num * 2;
  if (new_len > 1000) {
    return "";
  }
  char new_str[1000];
  int j = new_len - 1;
  new_str[new_len] = '\0';
  for (int i = len - 1; i >= 0; i--) {
    if (p[i] == ' ') {
      new_str[j] = '0';
      new_str[j - 1] = '2';
      new_str[j - 2] = '%';
      j = j - 3;
    } else {
      new_str[j] = p[i];
      j--;
    }
  }
  char *ret = (char *)malloc(new_len + 1);
  strcpy(ret, new_str);
  return ret;
}