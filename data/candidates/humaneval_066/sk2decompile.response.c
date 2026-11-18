int _hash(char *str) {
  int i, sum = 0;
  for (i = 0; str[i]; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') sum += str[i];
  }
  return sum;
}