static int json_get_escape_len(const char *s, int len) {
  switch (s[0]) {
    case '"':
    case '\\':
    case '/':
    case 'b':
    case 'f':
    case 'n':
    case 'r':
    case 't':
      return len >= 2 ? 1 : -2;
    case 'u':
      return len >= 6 && json_isxdigit(s[1]) && json_isxdigit(s[2]) &&
                     json_isxdigit(s[3]) && json_isxdigit(s[4])
                 ? 5
                 : -1;
    default:
      return -1;
  }
}