void ceasar(char *s, int n) {
  int i, j;
  for (i = 0; s[i] != '\0'; i++) {
    if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) {
      for (j = 0; j < n; j++) {
        if (s[i] == 90) {
          s[i] = 65;
          s[i]--;
        }
        if (s[i] == 122) {
          s[i] = 97;
          s[i]--;
        }
        s[i]++;
      }
    }
  }
}