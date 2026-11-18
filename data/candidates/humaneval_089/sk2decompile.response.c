void func0(char *a, char *b) {
  int i;
  for (i = 0; a[i]; i++) {
    b[i] = (a[i] - 'a' + 4) % 26 + 'a';
  }
  b[i] = '\0';
}