bool __cdecl func0(const char *str)
{
  regex_t regex;
  bool has_invalid_chars;

  // Compile a regex to match any character that is NOT alphanumeric or a dot
  regcomp(&regex, "[^a-zA-Z0-9.]", REG_EXTENDED);

  // regexec returns 0 if a match is found, or REG_NOMATCH (1) if no match is found
  has_invalid_chars = (regexec(&regex, str, 0, NULL, 0) == REG_NOMATCH);

  regfree(&regex);
  
  return has_invalid_chars;
}