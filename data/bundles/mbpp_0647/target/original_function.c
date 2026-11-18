char** func0(const char* text, int* count) {
  int len = strlen(text);
  char** result = malloc(len * sizeof(char*));
  if (result == NULL) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  int current_word = 0;
  int start = 0;
  for (int i = 1; i <= len; i++) {
    if (isupper(text[i]) || text[i] == '\0') {
      int word_length = i - start;
      result[current_word] = malloc(word_length + 1);
      if (result[current_word] == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
      }
      memcpy(result[current_word], text + start, word_length);
      result[current_word][word_length] = '\0';
      start = i;
      current_word++;
    }
  }
  *count = current_word;
  return result;
}