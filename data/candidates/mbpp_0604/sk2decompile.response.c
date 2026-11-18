char *func0(char *str) {
  char *tokens[10];
  char *token;
  int count;
  char *str1;
  str1 = str;
  count = 0;
  token = strtok(str1, " ");
  while (token != NULL) {
    tokens[count++] = token;
    token = strtok(NULL, " ");
  }
  str2[0] = '\0';
  for (int i = count - 1; i >= 0; i--) {
    strcat(str2, tokens[i]);
    if (i > 0) {
      strcat(str2, " ");
    }
  }
  return str2;
}