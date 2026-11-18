int func0(char *s) {
  char *token = strtok(s, " ");
  while (token != NULL) {
    if (strlen(token) % 2 != 0) {
      return 1;
    } else {
      return 0;
    }
    token = strtok(NULL, " ");
  }
  return 0;
}