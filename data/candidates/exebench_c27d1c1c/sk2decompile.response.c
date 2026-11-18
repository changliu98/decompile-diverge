void reverse(char *str) {
  char *begin = str;
  char *end = str;
  char temp;
  if (str) {
    while (*end) {
      end++;
    }
    end--;
    while (begin < end) {
      temp = *end;
      *end-- = *begin;
      *begin++ = temp;
    }
  }
}