char *__cdecl func0(const char *email)
{
  regex_t regex;
  const char *regex_pattern = "^[a-z0-9]+[\\._]?[a-z0-9]+[@]\\w+[.]\\w{2,3}$";
  
  // regcomp flag 9 corresponds to REG_EXTENDED (1) | REG_NOSUB (8)
  if (regcomp(&regex, regex_pattern, REG_EXTENDED | REG_NOSUB))
  {
    return "Invalid Email";
  }

  int ret = regexec(&regex, email, 0, NULL, 0);
  regfree(&regex);

  if (ret == 0)
    return "Valid Email";
  else
    return "Invalid Email";
}