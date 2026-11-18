const char *__cdecl func0(const char *text)
{
  regex_t regex;
  int ret;

  // REG_EXTENDED (1) is used to compile the regular expression "ab*?"
  if (regcomp(&regex, "ab*?", REG_EXTENDED))
    return "Error compiling regex";

  // Execute the regex against the input text
  ret = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);

  // Evaluate the result of the regex execution
  if (!ret) // regexec returns 0 on a successful match
    return "Found a match!";
  if (ret == REG_NOMATCH) // REG_NOMATCH is standardly defined as 1
    return "Not matched!";
  return "Regex match failed";
}