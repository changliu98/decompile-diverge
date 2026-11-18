int func0(int n) {
  char str[11];
  sprintf(str, "%d", n);
  int len = strlen(str);
  int i;
  for (i = len - 2; i >= 0; i--) {
    if (str[i] < str[i + 1]) {
      char str2[11];
      strcpy(str2, str + i);
      int len2 = strlen(str2);
      char min = str2[1];
      int j;
      for (j = 1; j < len2; j++) {
        if (str2[j] > str2[0] && str2[j] < min) {
          min = str2[j];
        }
      }
      int k;
      for (k = 0; k < len2; k++) {
        if (str2[k] == min) {
          int l;
          for (l = k; l < len2 - 1; l++) {
            str2[l] = str2[l + 1];
          }
          str2[len2 - 1] = '\0';
          break;
        }
      }
      qsort(str2, strlen(str2), sizeof(char), cmp);
      str[i] = min;
      strcpy(str + i + 1, str2);
      return atoi(str);
    }
  }
  return 0;
}