int _is_number(char *str) {
  int len = strlen(str);
  int i;
  while (*str == ' ') {
    str++;
    len--;
  }
  if (len < 1) return -1;
  if (*str == '+' || *str == '-') {
    for (i = 1; i < len; i++) {
      if (str[i] < '0' || str[i] > '9') return 0;
    }
    return 1;
  } else {
    for (i = 0; i < len; i++) {
      if (str[i] < '0' || str[i] > '9') return 0;
    }
    return 1;
  }
}