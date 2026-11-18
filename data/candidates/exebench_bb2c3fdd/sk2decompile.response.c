void reverse(char *s) {
  int i, len;
  char *p, temp;
  len = 0;
  for (p = s; *p != '\0'; p++) len++;
  for (i = 0; i <= len / 2 - 1; i++) {
    temp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = temp;
  }
}