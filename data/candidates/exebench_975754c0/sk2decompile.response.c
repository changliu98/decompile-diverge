void reverse(char *s) {
  int i, len;
  char temp;
  for (i = 0; s[i] != '\0'; i++)
    ;
  len = i;
  for (i = 0; i < len / 2; i++) {
    temp = s[i];
    s[i] = s[len - (i + 1)];
    s[len - (i + 1)] = temp;
  }
}