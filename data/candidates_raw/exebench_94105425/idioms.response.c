void reverse(char *str)
{
  char *start = str;
  char *end = str;
  while (1) {
    char next = *end != '\0';
    if (!next) {
      break;
    }
    end++;
  }
  end--;
  while (start < end) {
    char tmp = *start;
    *start = *end;
    *end = tmp;
    start++;
    end--;
  }
}