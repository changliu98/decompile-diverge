void strrev(char *str) {
  int i, j, k;
  char temp;
  for (i = 0; str[i] != '\0'; i++)
    ;
  i--;
  k = i;
  for (j = 0; j < k; j++, k--) {
    temp = str[k];
    str[k] = str[j];
    str[j] = temp;
  }
}