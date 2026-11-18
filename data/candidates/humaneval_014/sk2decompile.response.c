char **func0(char *s, int *n) {
  int len = strlen(s);
  char **res = malloc(len * sizeof(char *));
  char *tmp = malloc(len + 1);
  tmp[0] = '\0';
  for (int i = 0; i < len; i++) {
    int tmplen = strlen(tmp);
    tmp = realloc(tmp, tmplen + 2);
    tmp[tmplen] = s[i];
    tmp[tmplen + 1] = '\0';
    res[i] = malloc(strlen(tmp) + 1);
    strcpy(res[i], tmp);
  }
  free(tmp);
  *n = len;
  return res;
}