char *_camel_case(const char *str, char *buf) {
  int i = 0;
  int j = 0;
  int next_upper = 1;
  while (str[i]) {
    if (str[i] == '_') {
      next_upper = 1;
    } else if (next_upper) {
      buf[j++] = toupper(str[i]);
      next_upper = 0;
    } else {
      buf[j++] = str[i];
    }
    i++;
  }
  buf[j] = '\0';
  return buf;
}