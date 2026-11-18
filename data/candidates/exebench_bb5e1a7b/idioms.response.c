char *ReadNumber(char *str, double *res)
{
  char *s = str;
  double sign = 1.0;
  while (1) {
    int issign = 1;
    if (*s != '+')
      issign = *s == '-';
    if (!issign)
      break;
    if (*s == '-')
      sign = -sign;
    s++;
  }
  int i = 0;
  int d = 0;
  double ddiv = 1.0;
  while (1) {
    int isdigit = 0;
    if (*s <= '9')
      isdigit = *s >= '0';
    if (!isdigit)
      break;
    d = d * 10 + *s++ - '0';
  }
  if (*s == '\0') {
    *res = sign * d;
    return s;
  }
  if (*s == '.') {
    s++;
    while (1) {
      int isdigit = 0;
      if (*s <= '9')
        isdigit = *s >= '0';
      if (!isdigit)
        break;
      d = d * 10 + *s++ - '0';
      ddiv = ddiv * 10.0;
    }
  }
  *res = sign * (d + (double) d / ddiv);
  return s;
}