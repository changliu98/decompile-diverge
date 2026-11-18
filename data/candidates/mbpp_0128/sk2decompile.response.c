char **func0(int max, char *str, int *count) {
  char *token;
  int i = 0;
  token = strtok(str, " ");
  while (token != NULL) {
    if (strlen(token) > max) {
      words[i++] = token;
    }
    token = strtok(NULL, " ");
  }
  *count = i;
  return words;
}