void strip(char *str) {
  int i, j, k, l;
  if (str == NULL) return;
  for (j = 1; str[j] != '\0'; j++) {
    for (i = 0; i < j; i++) {
      if (str[i] == str[j]) {
        str[j] = -1;
        break;
      }
    }
  }
  k = 0;
  l = 0;
  for (j = 1; str[j] != '\0'; j++) {
    if (str[j] == -1) {
      k = j;
      while (str[j] == -1) j++;
      l = j;
      break;
    }
  }
  if (k == 0) return;
  while (str[l] != '\0') {
    if (str[l] != -1) {
      str[k++] = str[l];
      str[l++] = -1;
    } else {
      l++;
    }
  }
  str[k] = '\0';
}