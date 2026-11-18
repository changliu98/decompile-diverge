int func0(const char *text) {
  int len = strlen(text);
  int i;
  while (*text == ' ') {
    text++;
    len--;
  }
  if (len < 1) {
    return -1;
  } else {
    if (text[0] == '+' || text[0] == '-') {
      for (i = 1; i < len; i++) {
        if (text[i] < '0' || text[i] > '9') {
          return 0;
        }
      }
      return 1;
    } else {
      for (i = 0; i < len; i++) {
        if (text[i] < '0' || text[i] > '9') {
          return 0;
        }
      }
      return 1;
    }
  }
}