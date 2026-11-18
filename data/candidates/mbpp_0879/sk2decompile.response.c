char *func0(char *input) {
  regex_t regex;
  int status;
  if (regcomp(&regex, "a.*?b$", 1) != 0) {
    return "Regex compilation failed.";
  }
  status = regexec(&regex, input, 0, NULL, 0);
  if (!status) {
    return "Found a match!";
  } else if (status == 1) {
    return "Not matched!";
  } else {
    return "Regex match failed.";
  }
}