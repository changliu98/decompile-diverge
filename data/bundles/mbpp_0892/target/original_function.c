char* func0(const char* text) {
  static char buffer[1024];
  regex_t regex;
  regmatch_t match;
  const char* cursor = text;
  char* bufptr = buffer;
  int err;
  err = regcomp(&regex, " +", REG_EXTENDED);
  if (err != 0) {
    return NULL;
  }
  while (*cursor != '\0') {
    if (regexec(&regex, cursor, 1, &match, 0) == 0) {
      memcpy(bufptr, cursor, match.rm_so);
      bufptr += match.rm_so;
      *bufptr++ = ' ';
      cursor += match.rm_eo;
    } else {
      strcpy(bufptr, cursor);
      break;
    }
  }
  regfree(&regex);
  return buffer;
}