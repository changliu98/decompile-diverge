const char *__cdecl func0(const char *text)
{
  regex_t regex;
  int match_result;

  // Compile the regular expression "a.*?b$" with REG_EXTENDED (flag 1)
  if (regcomp(&regex, "a.*?b$", REG_EXTENDED))
    return "Regex compilation failed.";

  // Execute the regular expression against the input text
  match_result = regexec(&regex, text, 0, NULL, 0);

  if (!match_result)
    return "Found a match!";
    
  if (match_result == REG_NOMATCH) // REG_NOMATCH is typically defined as 1
    return "Not matched!";

  return "Regex match failed.";
}