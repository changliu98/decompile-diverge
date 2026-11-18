int func0(char *str, char c) {
  int i, len, pos = -1;
  len = strlen(str);
  for (i = 0; i < len; i++) {
    if (str[i] == c) pos = i;
  }
  if (pos == -1)
    return -1;
  else
    return pos + 1;
}