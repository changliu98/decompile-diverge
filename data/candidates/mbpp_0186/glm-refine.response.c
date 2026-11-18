const char *__cdecl func0(const char *text, const char *pattern)
{
  regex_t regex;
  
  // Attempt to compile the regular expression
  if (regcomp(&regex, pattern, 0) != 0)
    return "Regex compilation failed!";
  
  // Execute the regular expression
  int reti = regexec(&regex, text, 0, NULL, 0);
  
  // Free the compiled regex
  regfree(&regex);
  
  // Return appropriate string based on match status
  if (reti == 0)
    return "Matched!";
  else
    return (const char *)&unk_201E; // Likely "No match!" or similar failure string
}