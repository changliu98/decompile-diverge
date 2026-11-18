const char *func0(const char *text)
{
  regex_t regex;
  const char *result;

  // Compile the regular expression "ab?" with REG_EXTENDED (flag 1)
  if (regcomp(&regex, "ab?", REG_EXTENDED) != 0)
    return "Not matched!";

  // Execute the regex against the input text
  if (regexec(&regex, text, 0, NULL, 0) == 0)
    result = "Found a match!";
  else
    result = "Not matched!";

  regfree(&regex);
  return result;
}