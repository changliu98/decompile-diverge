char *func0(int *a, int n) {
  int found, i, j;
  int count;
  pair p[100];
  char *str;
  char temp[50];
  count = 0;
  for (j = 0; j < n; j++) {
    found = 0;
    for (i = 0; i < count; i++) {
      if (p[i].key == a[j]) {
        p[i].value++;
        found = 1;
        break;
      }
    }
    if (found == 0) {
      p[count].key = a[j];
      p[count].value = 1;
      count++;
    }
  }
  str = (char *)malloc(1000);
  str[0] = '\0';
  strcat(str, "{");
  for (j = 0; j < count; j++) {
    sprintf(temp, "%d: %d", p[j].key, p[j].value);
    strcat(str, temp);
    if (j < count - 1) {
      strcat(str, ", ");
    }
  }
  strcat(str, "}");
  return str;
}