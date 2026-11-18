void _rotate(char *str, int right) {
  int shift = right ? 5 : 21;
  size_t len = strlen(str);
  for (size_t i = 0; i < len; i++) {
    str[i] = (str[i] - 'a' + shift) % 26 + 'a';
  }
}