void reverse(char *s) {
  int i, j, k;
  char c;
  for (j = 0; s[j] != '\0'; j++)
    ;
  k = j - 1;
  if (s[k] == '\n') k--;
  for (i = 0; i < k; i++, k--) {
    c = s[i];
    s[i] = s[k];
    s[k] = c;
  }
}