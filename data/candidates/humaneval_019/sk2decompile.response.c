char *func0(char *s) {
  static char result[1000];
  int count[10];
  char *num[10];
  char temp[6];
  int i, j, k, l;
  memset(count, 0, sizeof(count));
  num[0] = "zero";
  num[1] = "one";
  num[2] = "two";
  num[3] = "three";
  num[4] = "four";
  num[5] = "five";
  num[6] = "six";
  num[7] = "seven";
  num[8] = "eight";
  num[9] = "nine";
  l = 0;
  while (*s) {
    k = 0;
    while (s[k] != ' ' && s[k] != '\0') {
      temp[k] = s[k];
      k++;
    }
    temp[k] = '\0';
    for (j = 0; j < 10; j++) {
      if (!strcmp(temp, num[j])) {
        count[j]++;
        break;
      }
    }
    s += k + 1;
  }
  for (k = 0; k < 10; k++) {
    for (j = 0; j < count[k]; j++) {
      for (i = 0; num[k][i] != '\0'; i++) {
        result[l] = num[k][i];
        l++;
      }
      result[l++] = ' ';
    }
  }
  if (l > 0)
    result[l - 1] = '\0';
  else
    result[0] = '\0';
  return result;
}