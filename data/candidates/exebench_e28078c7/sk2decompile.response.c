int parse_int(char *str, int *result) {
  int multiplier = 1;
  int is_negative;
  int i;
  int j;
  *result = 0;
  is_negative = (str[0] == '-');
  i = is_negative;
  for (j = 1; str[j] != '\0'; j++) {
    multiplier *= 10;
  }
  for (; str[i] != '\0'; i++) {
    int digit = str[i] - '0';
    if (digit > 9 || digit < 0) {
      return 0;
    }
    if (i > 0) {
      multiplier /= 10;
    }
    *result += digit * multiplier;
  }
  if (is_negative) {
    *result *= -1;
  }
  return 1;
}