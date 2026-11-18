bool __cdecl func0(const char *string)
{
  regex_t regex;

  // Compile the regular expression "^5"
  if (regcomp(&regex, "^5", 0) != 0)
  {
    fprintf(stderr, "Could not compile regex\n");
    return false;
  }

  // Execute the regex and store the match result
  int result = regexec(&regex, string, 0, NULL, 0);

  // Free the memory allocated by regcomp
  regfree(&regex);

  // regexec returns 0 on a successful match
  return result == 0;
}