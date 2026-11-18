char *func0(int n) {
  int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  char *numerals[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                      "XL", "X",  "IX", "V",  "IV", "I"};
  static char result[10];
  int i;
  int j;
  result[0] = '\0';
  i = 0;
  while (n > 0) {
    while (n >= values[i]) {
      strcat(result, numerals[i]);
      n -= values[i];
    }
    i++;
  }
  return result;
}