void sort(char *str) {
  int i, j;
  char temp;
  for (i = 1; i < 10; i++) {
    for (j = 0; j < 10 - i && str[j] != '\0'; j++) {
      if (str[j] > str[j + 1]) {
        temp = str[j];
        str[j] = str[j + 1];
        str[j + 1] = temp;
      }
    }
  }
}