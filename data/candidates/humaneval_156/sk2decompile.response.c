void func0(int n, char *s) {
  char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L",
                   "XL", "X", "IX", "V", "IV", "I"};
  int arabic[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  int i = 0;
  s[0] = '\0';
  while (n > 0) {
    while (n >= arabic[i]) {
      strcat(s, roman[i]);
      n -= arabic[i];
    }
    if (n > 0) {
      i++;
    }
  }
}