int reverse(char *str) {
  char *start = str;
  char *end = str;
  while (*end++)
    ;
  end--;
  end--;
  while (start < end) {
    *start ^= *end;
    *end ^= *start;
    *start ^= *end;
    start++;
    end--;
  }
  return 0;
}