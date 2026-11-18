void set_nb(char *str, char c, int *nb) {
  int i;
  int j;
  i = 0;
  j = 0;
  while (str[i]) {
    if (i == j && str[i] == c) {
      i++;
      j++;
    } else if (str[j] == c || str[j] == '\0') {
      *nb = *nb + 1;
      i = j;
    } else
      j++;
  }
}