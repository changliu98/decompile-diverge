const char *__cdecl func0(const char *text)
{
  regex_t regex;
  regmatch_t matches[1];

  // Compile the regular expression pattern.
  // REG_EXTENDED (1) is used to enable extended regular expressions.
  if (regcomp(&regex, "\\w+\\S*$", REG_EXTENDED) != 0)
    return "Regex compilation failed";

  // Execute the regular expression against the input text.
  if (regexec(&regex, text, 1, matches, 0) == 0)
  {
    regfree(&regex);
    return "Found a match!";
  }
  else
  {
    regfree(&regex);
    return "Not matched!";
  }
}