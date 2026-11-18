void reverse(char *str) {
  char *end = str;
  char *start = str;
  char *temp;
  while (*end) end++;
  temp = end - 1;
  while (start < temp) {
    *start ^= *temp;
    *temp ^= *start;
    *start ^= *temp;
    start++;
    temp--;
  }
}