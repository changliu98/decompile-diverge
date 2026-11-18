void numericCrypt(char *str) {
  int i, j;
  char *key = "aOizeasgtbq";
  char *value = "01234567890";
  for (i = 0; str[i] != '\0'; i++) {
    for (j = 0; key[j] != '\0'; j++) {
      if (str[i] == key[j]) {
        str[i] = value[j];
        break;
      }
    }
  }
}