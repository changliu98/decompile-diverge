void squeeze_all(char s1[], char s2[]) {
  int i, j, found;
  i = 0;
  for (j = 0; s1[j] != '\0'; j++) {
    found = 0;
    for (int k = 0; s2[k] != '\0'; k++) {
      if (s1[j] == s2[k]) {
        found = 1;
      }
    }
    if (!found) {
      s1[i++] = s1[j];
    }
  }
  s1[i] = '\0';
}