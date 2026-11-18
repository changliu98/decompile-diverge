void reverse(char *s) {
  int i, j;
  char c;
  i = 0;
  while (s[i] != '\0' && s[i] != '\n') i++;
  j = i - 1;
  i = 0;
  while (i < j) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
    i++;
    j--;
  }
}