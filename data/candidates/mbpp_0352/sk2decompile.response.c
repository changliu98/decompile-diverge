bool _isUnique(char *str) {
  int i, j;
  for (i = 0; i < strlen(str); i++) {
    for (j = i + 1; j < strlen(str); j++) {
      if (str[i] == str[j]) {
        return false;
      }
    }
  }
  return true;
}