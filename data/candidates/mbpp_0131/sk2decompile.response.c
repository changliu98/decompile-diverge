char *func0(char *str) {
  char *p = str;
  int i = 0;
  char vowels[100];
  int j;
  char c;
  int k;
  memset(vowels, 0, 100);
  for (j = 0; p[j] != '\0'; j++) {
    c = p[j];
    if (strchr("aeiouAEIOU", c) != NULL) {
      vowels[i++] = c;
    }
  }
  vowels[i] = '\0';
  i = 0;
  k = strlen(vowels) - 1;
  for (j = 0; p[j] != '\0'; j++) {
    if (strchr("aeiouAEIOU", p[j]) != NULL) {
      result[i++] = vowels[k--];
    } else {
      result[i++] = p[j];
    }
  }
  result[i] = '\0';
  return result;
}