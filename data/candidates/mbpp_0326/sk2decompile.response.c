char *_get_most_frequent_word(int argc, char **argv) {
  int word_count = 0;
  char word[50];
  char *p;
  int i, j, k, found;
  int max_count, max_index;
  for (i = 0; i < argc; i++) {
    p = argv[i];
    j = 0;
    while (*p) {
      if (isspace(*p)) {
        if (j > 0) {
          word[j] = '\0';
          found = 0;
          for (k = 0; k < word_count; k++) {
            if (!strcmp(words[k].word, word)) {
              words[k].count++;
              found = 1;
              break;
            }
          }
          if (!found) {
            strcpy(words[word_count].word, word);
            words[word_count].count = 1;
            word_count++;
          }
          j = 0;
        }
      } else {
        word[j++] = *p;
      }
      p++;
    }
    if (j > 0) {
      word[j] = '\0';
      found = 0;
      for (k = 0; k < word_count; k++) {
        if (!strcmp(words[k].word, word)) {
          words[k].count++;
          found = 1;
          break;
        }
      }
      if (!found) {
        strcpy(words[word_count].word, word);
        words[word_count].count = 1;
        word_count++;
      }
    }
  }
  max_count = 0;
  max_index = 0;
  for (i = 0; i < word_count; i++) {
    if (words[i].count > max_count) {
      max_count = words[i].count;
      max_index = i;
    }
  }
  return words[max_index].word;
}