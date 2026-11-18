void trim(char *s) {
  int i;
  for (i = 0; s[i] != '\0'; i++)
    ;
  s[i - 1] = '\0';
}