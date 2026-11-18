int func0(const char *str1) {
  int total = 0;
  while (*str1) {
    total++;
    str1++;
  }
  return total;
}