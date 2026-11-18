void _strrev(char *str, char *rev) {
  int len = strlen(str);
  int i;
  char c;
  for (i = 0; i < len; i++) {
    c = str[i];
    if (c >= 'a' && c <= 'z') {
      c -= 32;
    } else if (c >= 'A' && c <= 'Z') {
      c += 32;
    }
    rev[i] = c;
  }
  rev[len] = '\0';
}