char **func0(const char *str, int *count) {
  char **result = NULL;
  *count = 0;
  int len = strlen(str);
  int i = 0;
  while (i < len) {
    if (!isalpha((unsigned char)str[i])) {
      i++;
      continue;
    }
    int start = i;
    i++;
    while (i < len && !isalpha((unsigned char)str[i])) {
      i++;
    }
    int word_len = i - start;
    char *word = malloc(word_len + 1);
    strncpy(word, str + start, word_len);
    word[word_len] = '\0';
    result = realloc(result, (*count + 1) * sizeof(char *));
    result[*count] = word;
    (*count)++;
  }
  return result;
}