const char *__cdecl func0(const char *text)
{
  regex_t regex;

  // Compile the regular expression "ab*?" with REG_ICASE (case-insensitive)
  if (regcomp(&regex, "ab*?", REG_ICASE))
    return "Regex compilation failed";

  // Execute the regular expression against the input text
  int matched = !regexec(&regex, text, 0, NULL, 0);
  
  regfree(&regex);

  return matched ? "Found a match!" : "Not matched!";
}