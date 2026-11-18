void reverse(char *s) {
  int i, j;
  char c;
  for (j = 0; s[j] != '\0'; j++)
    ;
  for (i = 0; i < j / 2; i++) {
    c = s[i];
    s[i] = s[j - i - 1];
    s[j - i - 1] = c;
  }
}