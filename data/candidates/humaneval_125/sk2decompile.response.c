char **func0(char *str, int *count) {
  int j = 0;
  int odd_count = 0;
  int word_count = 0;
  int len = strlen(str);
  char **words = NULL;
  char word[101];
  memset(word, 0, 101);
  if (strchr(str, ' ') == NULL && strchr(str, ',') == NULL) {
    int i;
    for (i = 0; i < len; i++) {
      if (isalpha(str[i]) && (str[i] - 'a') % 2 == 1) {
        odd_count++;
      }
    }
    words = (char **)malloc(sizeof(char *));
    words[0] = (char *)malloc(12);
    sprintf(words[0], "%d", odd_count);
    word_count = 1;
  } else {
    words = (char **)malloc(sizeof(char *) * (len + 1));
    int i;
    for (i = 0; i <= len; i++) {
      if (str[i] != ' ' && str[i] != ',' && str[i] != '\0') {
        word[j++] = str[i];
      } else {
        if (j > 0) {
          word[j] = '\0';
          words[word_count] = strdup(word);
          word_count++;
          j = 0;
        }
      }
    }
  }
  *count = word_count;
  return words;
}