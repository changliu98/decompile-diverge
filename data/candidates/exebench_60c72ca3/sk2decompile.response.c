void string_rip(char *str, const char *chars) {
  char *src = str;
  char *dst = str;
  while (*src) {
    const char *ch = chars;
    int found = 0;
    while (*ch) {
      if (*src == *ch) {
        found = 1;
        break;
      }
      ch++;
    }
    if (found) {
      src++;
    } else {
      *dst++ = *src++;
    }
  }
  *dst = '\0';
}