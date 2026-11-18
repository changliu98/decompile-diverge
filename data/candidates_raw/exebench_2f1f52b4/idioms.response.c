int is_valid_utf8(char *str, int len)
{
  char *end = str + len;
  char c;
  int first;
  switch (len) {
  case 1:
    return (str[0] < 0x80 || str[0] >= 0xc2) && str[0] <= 0xf4;
  case 2:
  case 3:
    end -= 1;
    c = *end--;
    if (c < 0x80 || c > 0xbf)
      return 0;
  case 4:
    c = *end--;
    if (c < 0x80 || c > 0xbf)
      return 0;
  case 5:
    c = *end--;
    if (c > 0xbf)
      return 0;
    first = str[0];
    if (first == 0xe0 && c < 0xa0)
      return 0;
    if (first == 0xf0 && c < 0x90)
      return 0;
    if (first == 0xf4 && c > 0x8f)
      return 0;
    if (c < 0x80 || c >= 0xc2)
      return 0;
    return (str[0] < 0x80 || str[0] >= 0xc2) && str[0] <= 0xf4;
  default:
    return 0;
  }
}