const char *__cdecl func0(const char *text)
{
  regex_t regex;

  // Compile the regular expression: "[A-Z]+[a-z]+$" with the REG_EXTENDED flag
  regcomp(&regex, "[A-Z]+[a-z]+$", REG_EXTENDED);

  // Execute the regular expression against the input text
  // Note: regexec returns 0 on a successful match, and non-zero on failure
  if (regexec(&regex, text, 0, NULL, 0))
    return "Not matched!";
  else
    return "Found a match!";
}