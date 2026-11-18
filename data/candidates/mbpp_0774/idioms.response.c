char *func0(char *email)
{
  int ret;
  char *email_pattern = "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$";
  struct regex_t regex;
  if (regcomp(&regex, email_pattern, (1 << 1) | (1 << 2)))
    return "Invalid Email";
  ret = regexec(&regex, email, 0, ((void *)0), 0);
  regfree(&regex);
  if (ret)
    return "Invalid Email";
  return "Valid Email";
}