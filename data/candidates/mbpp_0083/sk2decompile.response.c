int _get_next_char(char *str) {
  int i, sum = 0;
  for (i = 0; str[i]; i++) {
    sum += str[i] - 'a' + 1;
  }
  if (sum % 26)
    return sum % 26 + 'a' - 1;
  else
    return 'z';
}