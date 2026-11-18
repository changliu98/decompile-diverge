int func0(char *a, char *b) {
  int i, j, a1, a2, b1, b2;
  char temp1[101], temp2[101];
  for (i = 0; a[i] != '/'; i++) temp1[i] = a[i];
  temp1[i] = '\0';
  a1 = atoi(temp1);
  j = 0;
  i++;
  while (a[i] != '\0') {
    temp2[j] = a[i];
    j++;
    i++;
  }
  temp2[j] = '\0';
  a2 = atoi(temp2);
  for (i = 0; b[i] != '/'; i++) temp1[i] = b[i];
  temp1[i] = '\0';
  b1 = atoi(temp1);
  j = 0;
  i++;
  while (b[i] != '\0') {
    temp2[j] = b[i];
    j++;
    i++;
  }
  temp2[j] = '\0';
  b2 = atoi(temp2);
  if (a1 * b1 % (a2 * b2) == 0)
    return 1;
  else
    return 0;
}