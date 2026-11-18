char* func0(const char* email) {
  const char* regex_pattern = "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$";
  regex_t regex;
  int ret;
  ret = regcomp(&regex, regex_pattern, REG_EXTENDED | REG_NOSUB);
  if (ret) {
    return "Invalid Email";
  }
  ret = regexec(&regex, email, 0, NULL, 0);
  regfree(&regex);
  if (!ret) {
    return "Valid Email";
  } else {
    return "Invalid Email";
  }
}