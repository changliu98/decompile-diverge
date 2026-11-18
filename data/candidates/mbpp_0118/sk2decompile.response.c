char **_strsplit(const char *str) {
  char **ret;
  char *str_copy;
  char *token;
  int i;
  int num_tokens = 1;
  const char *p;
  for (p = str; *p != '\0'; p++) {
    if (*p == ' ') {
      num_tokens++;
    }
  }
  ret = malloc((num_tokens + 1) * sizeof(char *));
  if (ret == NULL) {
    return NULL;
  }
  str_copy = strdup(str);
  if (str_copy == NULL) {
    free(ret);
    return NULL;
  }
  i = 0;
  token = strtok(str_copy, " ");
  while (token != NULL) {
    ret[i++] = strdup(token);
    token = strtok(NULL, " ");
  }
  ret[i] = NULL;
  free(str_copy);
  return ret;
}