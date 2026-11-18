int ISORegexp__get_cclass(char *pattern, int i, int *len, int *start, int *end,
                          int *anchor) {
  int type;
  if (pattern[i] == '^') {
    i++;
    *anchor = 1;
  } else {
    *anchor = 0;
  }
  switch (pattern[i]) {
    case ' ':
      *len = 1;
      return 3;
    case '%':
      i++;
      *len = 2;
      switch (pattern[i]) {
        case 'c':
          type = 1;
          break;
        case 'd':
          type = 2;
          break;
        case 'i':
          type = 5;
          break;
        case 'p':
          type = 6;
          break;
        case 'C':
          type = 4;
          break;
        case 'P':
          type = 7;
          break;
        case 't':
          type = 9;
          break;
        default:
          *start = i;
          *end = i;
          type = 8;
          break;
      }
      break;
    case '[':
      *start = i + 2;
      while (pattern[i] && pattern[i] != ']') i++;
      *end = i - 1;
      *len = *end - *start + 1;
      type = 8;
      break;
    default:
      *len = 1;
      *start = i;
      *end = i;
      type = 8;
      break;
  }
  return type;
}