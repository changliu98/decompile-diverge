char *func0(const char *string) {
  regex_t regex;
  static char buf[100];
  char match[100];
  regmatch_t pmatch[1];
  int reti;
  int start;
  int end;
  reti = regcomp(&regex, "\\w+ly", 1);
  if (reti) {
    printf("Could not compile regex\n");
    return NULL;
  }
  reti = regexec(&regex, string, 1, pmatch, 0);
  if (!reti) {
    start = pmatch[0].rm_so;
    end = pmatch[0].rm_eo;
    strncpy(match, string + start, end - start);
    match[end - start] = 0;
    snprintf(buf, 100, "%d-%d: %s", start, end, match);
    regfree(&regex);
    return buf;
  } else {
    regfree(&regex);
    return NULL;
  }
}