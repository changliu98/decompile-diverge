int unquote(char *in, int percent, unsigned long *len)
{
  char *inptr = in;
  char *outptr = in;
  char c;
  while (1) {
    c = *inptr;
    if (c == '\0') {
      *outptr = '\0';
      *len = (outptr - in);
      return 0;
    }
    if (c == '\\') {
      switch (*++inptr) {
      case '\0':
        *outptr = '\\';
        outptr[1] = '\0';
        *len = (outptr - in + 1);
        return 0;
      case '\\':
      case '\'':
        *outptr = c;
        break;
      case 'a':
        *outptr = '\a';
        break;
      case 'b':
        *outptr = '\b';
        break;
      case 'f':
        *outptr = '\f';
        break;
      case 'n':
        *outptr = '\n';
        break;
      case 'r':
        *outptr = '\r';
        break;
      case 't':
        *outptr = '\t';
        break;
      case 'v':
        *outptr = '\v';
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        {
          int i;
          int max;
          int iszero;
          char *p;
          iszero = 0;
          if (!percent)
            iszero = *inptr == '0';
          max = (iszero ? 4 : 3);
          for (i = 0, p = inptr; ; i = i * 8 + *p - '0', p++) {
            if (max-- == 0
                || !((*p >= '0') && (*p <= '7')))
              break;
          }
          p--;
          if (percent && i == '%') {
            *outptr++ = '%';
            *outptr = '%';
          } else
            *outptr = i;
        }
        break;
      case 'c':
        if (percent) {
          *outptr = c;
        } else {
          *outptr = '\0';
          *len = (outptr - in);
          return 1;
        }
        break;
      default:
        *outptr = c;
      }
    } else
      *outptr = c;
    inptr++;
    outptr++;
  }
}