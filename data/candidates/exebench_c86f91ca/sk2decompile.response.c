void remove_dupc2(char *str) {
  int i, j, k;
  for (j = 0; str[j] != '\0'; j++) {
    if (str[j] != -1) {
      for (i = j + 1; str[i] != '\0'; i++) {
        if (str[j] == str[i]) {
          str[i] = -1;
        }
      }
    }
  }
  for (i = 0; str[i] != '\0' && str[i] != -1; i++)
    ;
  if (str[i] == '\0')
    k = j - 1;
  else
    k = i;
  for (i = k + 1; str[i] != '\0'; i++) {
    if (str[i] != -1) {
      str[k++] = str[i];
    }
  }
  str[k] = str[i];
}