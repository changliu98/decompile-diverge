char** func0(const char* text, int* count) {
  int n = strlen(text);
  char** result = malloc(n * sizeof(char*));
  *count = 0;
  int word_start = 0;
  for (int i = 1; i <= n; i++) {
    if (i == n || (isupper(text[i]) && !isupper(text[i - 1]))) {
      int word_length = i - word_start;
      result[*count] = malloc((word_length + 1) * sizeof(char));
      strncpy(result[*count], text + word_start, word_length);
      result[*count][word_length] = '\0';
      (*count)++;
      word_start = i;
    }
  }
  return result;
}