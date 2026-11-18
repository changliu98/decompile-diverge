const char *__cdecl func0(const char *text)
{
  regex_t regex;
  int regcomp_res;
  int regexec_res;

  // Compile the regular expression. 
  // The '1' flag corresponds to REG_EXTENDED (use extended POSIX regex).
  regcomp_res = regcomp(&regex, MATCH_PATTERN, REG_EXTENDED);
  
  if (regcomp_res != 0)
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Error";
  }

  // Execute the regular expression against the input text.
  // 0LL / 0 are used for nmatch, pmatch, and eflags (no substring extraction, no special flags).
  regexec_res = regexec(&regex, text, 0, NULL, 0);
  
  // Free the memory allocated by regcomp
  regfree(&regex);

  // regexec returns 0 on a successful match, and REG_NOMATCH (1) on failure
  if (regexec_res == 0)
  {
    return "Found a match!";
  }
  else
  {
    return "Not matched!";
  }
}