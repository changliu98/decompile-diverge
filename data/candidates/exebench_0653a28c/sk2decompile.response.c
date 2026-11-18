void reverse(char *s) {
  char *end = s;
  char *begin = s;
  char temp;
  while (*end++)
    ;
  end--;
  end--;
  while (begin < end) {
    temp = *begin;
    *begin = *end;
    *end = temp;
    begin++;
    end--;
  }
}