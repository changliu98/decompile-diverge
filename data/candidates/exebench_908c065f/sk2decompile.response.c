void reverse(char *str) {
  char *end = str;
  char *begin = str;
  char temp;
  while (*end) {
    end++;
  }
  end--;
  while (begin < end) {
    temp = *begin;
    *begin = *end;
    *end = temp;
    begin++;
    end--;
  }
}