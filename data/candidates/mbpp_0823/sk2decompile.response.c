char *func0(char *str, char *substr) {
  if (strstr(str, substr) == NULL) {
    return "entered string isnt a substring";
  }
  char regex[100];
  memset(regex, 0, 100);
  regex[0] = '^';
  strcat(regex, substr);
  regex_t preg;
  regcomp(&preg, regex, 0);
  int x = regexec(&preg, str, 0, NULL, 0);
  regfree(&preg);
  if (x == 0) {
    return "string starts with the given substring";
  } else {
    return "string doesnt start with the given substring";
  }
}