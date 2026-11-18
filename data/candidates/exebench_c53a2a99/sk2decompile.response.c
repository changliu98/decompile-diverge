void unhide(char *str) {
  char *p = str;
  int i = 0;
  int key[3] = {1, 3, 2};
  int j;
  for (j = 0; p[j] != '\0'; j++) {
    p[j] -= key[i];
    i++;
    if (i == 3) i = 0;
  }
}