char *str_rev(char *str) {
  char *start = str;
  char *end = str;
  char temp;
  while (*end++)
    ;
  end--;
  end--;
  while (start < end) {
    temp = *start;
    *start++ = *end;
    *end-- = temp;
  }
  return str;
}