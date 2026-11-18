char* func0(const char* text) {
  regex_t regex;
  char* pattern = "^[a-z]+_[a-z]+$";
  regcomp(&regex, pattern, REG_EXTENDED);
  int reti = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (!reti)
    return "Found a match!";
  else
    return "Not matched!";
}