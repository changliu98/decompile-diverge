char* func0(char** words, int wordsSize) {
  static char result[100];
  char** w = words;
  int size = wordsSize;
  int count = 0;
  int i, j, len;
  char temp[100];
  for (i = 0; i < size; i++) {
    for (j = i; j < size; j++) {
      len = strlen(w[i]);
      for (int k = 0; k < len; k++) {
        temp[k] = w[i][len - 1 - k];
      }
      temp[len] = '\0';
      if (!strcmp(w[j], temp)) {
        count++;
      }
    }
  }
  sprintf(result, "%d", count);
  return result;
}