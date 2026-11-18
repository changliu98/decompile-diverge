char *func0(char *email) {
  regex_t preg;
  int x;
  char *pattern = "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$";
  if (!regcomp(&preg, pattern, 1024 | 8)) {
    x = regexec(&preg, email, 0, NULL, 0);
    regfree(&preg);
    if (!x)
      return "Valid Email";
    else
      return "Invalid Email";
  } else
    return "Invalid Email";
}