bool __cdecl func0(const char *str)
{
  regex_t regex;
  bool is_match;

  // Compile the regular expression: matches any string ending with a digit
  if (regcomp(&regex, ".*[0-9]$", 0) != 0) {
    return false; 
  }

  // Execute the regular expression against the input string
  is_match = (regexec(&regex, str, 0, NULL, 0) == 0);

  // Free the memory allocated by regcomp
  regfree(&regex);

  return is_match;
}