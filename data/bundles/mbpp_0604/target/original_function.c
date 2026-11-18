char* func0(char* s) {
  static char result[100];
  int word_count = 0;
  char* words[10];
  char* token = strtok(s, " ");
  while (token != NULL) {
    words[word_count++] = token;
    token = strtok(NULL, " ");
  }
  result[0] = '\0';
  for (int i = word_count - 1; i >= 0; i--) {
    strcat(result, words[i]);
    if (i > 0) {
      strcat(result, " ");
    }
  }
  return result;
}