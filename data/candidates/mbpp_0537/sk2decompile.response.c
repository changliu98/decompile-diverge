char *func0(char *str) {
  char *arr[100];
  char *str1 = str;
  char *token;
  int i = 0;
  token = strtok(str1, " ");
  while (token != NULL) {
    int j;
    for (j = 0; j < i; j++) {
      if (!strcmp(arr[j], token)) {
        return token;
      }
    }
    arr[i++] = token;
    token = strtok(NULL, " ");
  }
  return "None";
}