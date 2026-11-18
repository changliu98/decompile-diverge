static char *getbase(char *s, int *base) {
  if (*s != '0') {
    *base = 10;
    return s;
  }
  switch (s[1]) {
    case 'o':
      *base = 8;
      s += 2;
      break;
    case 'x':
      *base = 16;
      s += 2;
      break;
    case 'n':
    case 't':
      *base = 10;
      s += 2;
      break;
    default:
      *base = 10;
      break;
  }
  return s;
}