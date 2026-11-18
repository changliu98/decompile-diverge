int *strtok_int(char *str, int *size)
{
  int i = 0;
  char *s = str;
  char *e;
  int v;
  for (s = str; *s != '\0'; s = e) {
    while (1) {
      int is_digit = *s != '\0' && ((*__ctype_b_loc ())[(int) ((*s))] & (unsigned short) _ISdigit);
      if (!is_digit && *s != '-')
        break;
      s++;
    }
    if (*s == '\0')
      break;
    v = strtol(s, &e, 10);
    if (e != s && (*e == ',' || *e == '\0')) {
      while (1) {
        int is_comma = *e != '\0' && *e != ',';
        if (!is_comma)
          break;
        e++;
      }
    } else {
      out[i++] = v;
    }
  }
  *size = i;
  return out;
}