char **_split_sentence(char *sentence) {
  char **words = malloc((strlen(sentence) / 2 + 1) * sizeof(char *));
  int i = 0;
  char *sentence_copy = strdup(sentence);
  char *word = strtok(sentence_copy, " ");
  while (word != NULL) {
    char *end = word + strlen(word) - 1;
    while (end > word && (*end == '.' || *end == ',' || *end == '!' ||
                          *end == '?' || *end == ';' || *end == ':')) {
      *end = '\0';
      end--;
    }
    if (strlen(word) >= 4) {
      words[i++] = strdup(word);
    }
    word = strtok(NULL, " ");
  }
  words[i] = NULL;
  free(sentence_copy);
  return words;
}