const char *__cdecl func0(const char *text)
{
  regex_t regex;
  int match_result;

  // Compile the regular expression to match strings starting with alphanumeric characters or underscores
  if (regcomp(&regex, "^[[:alnum:]_]+", REG_EXTENDED))
    return "Regex compilation error";

  // Execute the regular expression against the input text
  match_result = regexec(&regex, text, 0, NULL, 0);
  
  regfree(&regex);

  if (match_result == 0)
    return "Found a match!";
  else
    return "Not matched!";
}