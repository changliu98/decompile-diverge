char *string_to_slong(char *str, long *val)
{
  int c = *str;
  int sign = 0;
  if (c == '-') {
    sign = 1;
    str++;
    c = *str;
  }
  else if (c == '+') {
    str++;
    c = *str;
  }
  *val = 0;
  while (c >= '0' && c <= '9') {
    *val = *val * 10 + c - '0';
    str++;
    c = *str;
  }
  if (sign)
    *val = -*val;
  return str;
}