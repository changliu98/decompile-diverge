char **func0(const char *text) {
  char **result = malloc(sizeof(char *) * (strlen(text) / 2 + 1));
  int count = 0;
  char *copy = strdup(text);
  char *token = strtok(copy, " ");
  while (token != NULL) {
    char *end = token + strlen(token) - 1;
    while (end > token && (*end == '.' || *end == ',' || *end == '!' ||
                           *end == '?' || *end == ';' || *end == ':')) {
      *end = '\0';
      end--;
    }
    if (strlen(token) >= 4) {
      result[count++] = strdup(token);
    }
    token = strtok(NULL, " ");
  }
  result[count] = NULL;
  free(copy);
  return result;
}