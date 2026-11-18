void squeeze_alt(char s1[], char s2[]) {
  int i, j, k, found;
  k = 0;
  for (i = 0; s1[i] != '\0'; i++) {
    found = 0;
    for (j = 0; s2[j] != '\0' && found != 1; j++) {
      if (s1[i] == s2[j]) {
        found = 1;
      }
    }
    if (found == 0) {
      s1[k++] = s1[i];
    }
  }
  s1[k] = '\0';
}