char **func0(char **str, int n) {
  int count, i, j;
  char **str1;
  str1 = (char **)malloc(n * sizeof(char *));
  for (j = 0; j < n; j++) {
    count = 0;
    for (i = 0; str[j][i] != '\0'; i++) {
      if (str[j][i] >= '0' && str[j][i] <= '9') {
        if ((str[j][i] - '0') % 2 == 1) {
          count++;
        }
      }
    }
    str1[j] = (char *)malloc(100 * sizeof(char));
    sprintf(str1[j],
            "the number of odd elements %d in the string %d of the %d input.",
            count, count, count);
  }
  return str1;
}