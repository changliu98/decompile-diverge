const char *func0(const char *text)
{
  regex_t regex;
  int match_status;

  // Compile the regular expression "ab+" with REG_EXTENDED (flag 1)
  if (regcomp(&regex, "ab+", REG_EXTENDED) != 0)
    return "Regex compilation failed!";

  // Execute the regex against the provided text
  match_status = regexec(&regex, text, 0, NULL, 0);
  
  regfree(&regex);

  // regexec returns 0 on match, and REG_NOMATCH (1) otherwise
  if (match_status == 0)
    return "Found a match!";
  else
    return "Not matched!";
}