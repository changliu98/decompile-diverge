int func0(char *str) {
  char tmp[256];
  int i, j, max, k;
  max = 0;
  k = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] >= '0' && str[i] <= '9') {
      tmp[k++] = str[i];
    } else {
      if (k != 0) {
        tmp[k] = '\0';
        j = atoi(tmp);
        if (j > max) max = j;
        k = 0;
      }
    }
  }
  if (k != 0) {
    tmp[k] = '\0';
    j = atoi(tmp);
    if (j > max) max = j;
  }
  return max;
}