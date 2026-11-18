const char* func0(const char* text) {
  regex_t regex;
  int reti;
  char* pattern = "\\w*z.\\w*";
  reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compile error";
  }
  reti = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (!reti) {
    return "Found a match!";
  } else if (reti == REG_NOMATCH) {
    return "Not matched!";
  } else {
    char error_message[100];
    regerror(reti, &regex, error_message, sizeof(error_message));
    fprintf(stderr, "Regex match failed: %s\n", error_message);
    return "Regex match error";
  }
}