char* func0(const char* string, const char* sample) {
  if (strstr(string, sample) != NULL) {
    regex_t regex;
    int result;
    char pattern[100] = "^";
    strcat(pattern, sample);
    regcomp(&regex, pattern, 0);
    result = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);
    if (result == 0) {
      return "string starts with the given substring";
    } else {
      return "string doesnt start with the given substring";
    }
  } else {
    return "entered string isnt a substring";
  }
}