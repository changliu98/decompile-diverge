void squeeze(char s1[], char s2[]) {
  int i, j, k, flag;
  i = 0;
  j = 0;
  while (s1[i] != '\0') {
    flag = 0;
    for (k = 0; s2[k] != '\0'; k++) {
      if (s1[i] == s2[k]) {
        flag = 1;
      }
    }
    if (flag == 0) {
      s1[j++] = s1[i];
    }
    i++;
  }
  s1[j] = '\0';
}