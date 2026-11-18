char **func0(char *s, int *n) {
  int len = strlen(s);
  char **res = malloc(len * sizeof(char *));
  *n = 0;
  int start = 0;
  int i;
  for (i = 1; i <= len; i++) {
    if (i == len || (isalpha(s[i]) && !isalpha(s[i - 1]))) {
      int word_len = i - start;
      res[*n] = malloc(word_len + 1);
      strncpy(res[*n], s + start, word_len);
      res[*n][word_len] = '\0';
      (*n)++;
      start = i;
    }
  }
  return res;
}