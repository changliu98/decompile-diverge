char **func0(const char *str, int *num_words) {
  int len = strlen(str);
  char **words = malloc(len * sizeof(char *));
  if (words == NULL) {
    perror("Failed to allocate memory");
    exit(1);
  }
  int word_index = 0;
  int word_start = 0;
  int i;
  for (i = 1; i <= len; i++) {
    if (!isalnum(str[i]) && str[i] != '\0') {
      int word_len = i - word_start;
      words[word_index] = malloc(word_len + 1);
      if (words[word_index] == NULL) {
        perror("Failed to allocate memory");
        exit(1);
      }
      memcpy(words[word_index], str + word_start, word_len);
      words[word_index][word_len] = '\0';
      word_start = i;
      word_index++;
    }
  }
  *num_words = word_index;
  return words;
}