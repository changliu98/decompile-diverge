void reverse(char *s) {
  int len, i, j;
  for (len = 0; s[len] != '\0'; len++)
    ;
  j = 0;
  for (i = len - 1; j < i; i--) {
    char tmp = s[j];
    s[j] = s[i];
    s[i] = tmp;
    j++;
  }
}