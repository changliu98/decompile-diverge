char *_remove_duplicates(const char *str) {
  char *str_copy = strdup(str);
  if (str_copy == NULL) return NULL;
  char *words[100];
  int num_words = 0;
  char *word = strtok(str_copy, " ");
  while (word != NULL) {
    int found = 0;
    for (int i = 0; i < num_words; i++) {
      if (!strcmp(word, words[i])) {
        found = 1;
        break;
      }
    }
    if (!found) words[num_words++] = word;
    word = strtok(NULL, " ");
  }
  int new_str_len = 0;
  for (int i = 0; i < num_words; i++) new_str_len += strlen(words[i]) + 1;
  char *new_str = malloc(new_str_len);
  if (new_str == NULL) {
    free(str_copy);
    return NULL;
  }
  new_str[0] = '\0';
  for (int i = 0; i < num_words; i++) {
    strcat(new_str, words[i]);
    if (i < num_words - 1) strcat(new_str, " ");
  }
  free(str_copy);
  return new_str;
}