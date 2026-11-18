char** func0(int n, char* str, int* count) {
  static char* word_len[100];
  int index = 0;
  char* token = strtok(str, " ");
  while (token != NULL) {
    if (strlen(token) > n) {
      word_len[index++] = token;
    }
    token = strtok(NULL, " ");
  }
  *count = index;
  return word_len;
}