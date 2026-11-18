int func0(char *str) {
  char *token;
  token = strtok(str, " ");
  if (token == NULL) return 0;
  if (strlen(token) % 2 == 0) return 1;
  return 0;
}