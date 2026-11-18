char *func0(char *str) {
  int len = strlen(str);
  char *result = malloc(len + 2);
  int result_index = 0;
  int word_len = 0;
  char word[50];
  for (int i = 0; i <= len; i++) {
    if (str[i] == ' ' || str[i] == '\0') {
      for (int j = 0; j < word_len - 1; j++) {
        for (int k = j + 1; k < word_len; k++) {
          if (word[j] > word[k]) {
            char temp = word[j];
            word[j] = word[k];
            word[k] = temp;
          }
        }
      }
      if (result_index > 0) {
        result[result_index++] = ' ';
      }
      for (int j = 0; j < word_len; j++) {
        result[result_index++] = word[j];
      }
      word_len = 0;
    } else {
      word[word_len++] = str[i];
    }
  }
  result[result_index] = '\0';
  return result;
}