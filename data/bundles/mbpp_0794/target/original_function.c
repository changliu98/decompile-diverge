char* func0(const char* text) {
  regex_t regex;
  int result;
  char* pattern = "a.*?b$";
  result = regcomp(&regex, pattern, REG_EXTENDED);
  if (result) {
    fprintf(stderr, "Could not compile regex\n");
    return "Error";
  }
  result = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (result == 0) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}