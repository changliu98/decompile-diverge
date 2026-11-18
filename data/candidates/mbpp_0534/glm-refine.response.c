int __cdecl func0(const char *pattern, const char *text, int *start, int *end)
{
  regmatch_t match;
  regex_t regex;

  // Compile the regex pattern. 
  // The flag '1' corresponds to REG_EXTENDED (use POSIX extended regular expressions).
  if (regcomp(&regex, pattern, REG_EXTENDED))
    return -1;

  // Execute the regex search. 
  // Returns 0 on match, REG_NOMATCH (non-zero) on failure.
  int status = regexec(&regex, text, 1, &match, 0);
  
  // Free the memory allocated by regcomp
  regfree(&regex);

  if (status)
    return -1;

  // Store the match boundaries in the output pointers
  *start = match.rm_so;
  *end = match.rm_eo;

  return 0;
}