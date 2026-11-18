void sort(char *str) {
  int i, j, key;
  for (i = 0; str[i + 1] != '\0'; i++) {
    key = str[i + 1];
    j = i;
    while (str[j] > key && j > 0) {
      str[j + 1] = str[j];
      j--;
    }
    str[j + 1] = key;
  }
}