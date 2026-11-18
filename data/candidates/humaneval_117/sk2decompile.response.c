char **func0(char *str, int n, int *count) {
  char **result = NULL;
  int word_length = 0;
  int result_count = 0;
  int word_start = 0;
  int i = 0;
  size_t len = strlen(str);
  char *word = (char *)malloc(len + 1);
  for (i = 0; i <= len; i++) {
    if (isspace(str[i]) || str[i] == '\0') {
      if (word_length == n) {
        word[i - word_start] = '\0';
        result = (char **)realloc(result, (result_count + 1) * sizeof(char *));
        result[result_count] = (char *)malloc(strlen(word) + 1);
        strcpy(result[result_count], word);
        result_count++;
      }
      word_start = i + 1;
      word_length = 0;
    } else {
      word[i - word_start] = str[i];
      if (strchr("aeiouAEIOU", str[i]) == NULL && isalpha(str[i])) {
        word_length++;
      }
    }
  }
  free(word);
  *count = result_count;
  return result;
}