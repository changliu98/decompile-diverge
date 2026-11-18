int func0(char *s) {
  char *token = strtok(s, " ");
  if (token == ((void *)0)) {
    return 0;
  }
  int len = strlen(token);
  if (len % 2 == 0) {
    return 1;
  }
  return 0;
}