void squeeze(char s1[], char s2[]) {
  int i, j, k;
  for (j = 0, k = 0; s1[j] != '\0'; j++) {
    for (i = 0; s2[i] != '\0' && s1[j] != s2[i]; i++)
      ;
    if (s2[i] == '\0') {
      s1[k++] = s1[j];
    }
  }
  s1[k] = '\0';
}