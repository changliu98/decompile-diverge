void string_reverse(char *str) {
  char *start = str;
  char *end = str;
  char temp;
  while (*end) end++;
  while (start < end) {
    temp = *start;
    *start++ = *--end;
    *end = temp;
  }
}