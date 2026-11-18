const char* func0(int n, const char* test_list[]) {
  static WordCount words[100];
  int unique = 0;
  for (int i = 0; i < n; i++) {
    const char* str = test_list[i];
    char word[50];
    int pos = 0;
    while (*str) {
      if (!isspace(*str)) {
        word[pos++] = *str;
      }
      else {
        if (pos > 0) {
          word[pos] = '\0';
          int found = 0;
          for (int j = 0; j < unique; j++) {
            if (strcmp(words[j].word, word) == 0) {
              words[j].count++;
              found = 1;
              break;
            }
          }
          if (!found) {
            strcpy(words[unique].word, word);
            words[unique].count = 1;
            unique++;
          }
          pos = 0;
        }
      }
      str++;
    }
    if (pos > 0) {
      word[pos] = '\0';
      int found = 0;
      for (int j = 0; j < unique; j++) {
        if (strcmp(words[j].word, word) == 0) {
          words[j].count++;
          found = 1;
          break;
        }
      }
      if (!found) {
        strcpy(words[unique].word, word);
        words[unique].count = 1;
        unique++;
      }
    }
  }
  int max = 0;
  int index = 0;
  for (int i = 0; i < unique; i++) {
    if (words[i].count > max) {
      max = words[i].count;
      index = i;
    }
  }
  return words[index].word;
}