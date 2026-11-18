static const char *convert_set_sign(const char *str, int *sign) {
  const char *orig_str = str;
  *sign = 1;
  if (str) {
    if (*str == '+') {
      *sign = 1;
      str++;
    } else if (*str == '-') {
      *sign = -1;
      str++;
    }
  }
  return str;
}