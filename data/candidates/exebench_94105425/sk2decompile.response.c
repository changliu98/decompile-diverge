void strrev(char *str) {
  char *start, *end;
  start = str;
  end = str;
  while (end && *end) end++;
  end--;
  while (start < end) {
    *start ^= *end;
    *end ^= *start;
    *start ^= *end;
    start++;
    end--;
  }
}