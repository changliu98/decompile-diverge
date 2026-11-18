int escape(char *s, int cflag, int *len) {
  char *p, *q;
  char c;
  int n;
  char oct;
  p = q = s;
  while ((c = *p) != '\0') {
    if (c != '\\') {
      *q = c;
      p++;
      q++;
      continue;
    }
    p++;
    switch (*p) {
      case '\0':
        *q = '\\';
        q++;
        *q = '\0';
        *len = q - s;
        return 0;
      case 'a':
        *q = '\a';
        break;
      case 'b':
        *q = '\b';
        break;
      case 'c':
        if (cflag) {
          *q = 'c';
          break;
        }
        *q = '\0';
        *len = q - s;
        return 1;
      case 'f':
        *q = '\f';
        break;
      case 'n':
        *q = '\n';
        break;
      case 'r':
        *q = '\r';
        break;
      case 't':
        *q = '\t';
        break;
      case 'v':
        *q = '\v';
        break;
      case '\\':
      case '\'':
        *q = *p;
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        oct = (cflag || *p == '0') ? 4 : 3;
        n = 0;
        while (oct-- && *p >= '0' && *p <= '7') {
          n = (n << 3) + (*p - '0');
          p++;
        }
        p--;
        if (cflag && n == '%') {
          *q++ = '%';
          *q = '%';
        } else
          *q = n;
        break;
      default:
        *q = *p;
        break;
    }
    p++;
    q++;
  }
  *q = '\0';
  *len = q - s;
  return 0;
}