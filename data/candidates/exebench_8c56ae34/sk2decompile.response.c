void Reverse(char *s) {
  int i = 0, j;
  char c;
  for (j = 0; s[j] != '\0'; j++)
    ;
  j--;
  if (s[j] == '\n') j--;
  while (i < j) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
    j--;
    i++;
  }
}