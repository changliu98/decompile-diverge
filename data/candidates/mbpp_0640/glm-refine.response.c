char *__cdecl func0(char *item)
{
  char *result; 
  regmatch_t matches[2]; 
  regex_t regex; 

  // Allocate a mutable copy of the input string
  result = (char *)malloc(strlen(item) + 1);
  strcpy(result, item);

  // Compile regex: " ?\([^)]+\)" (REG_EXTENDED = 1)
  if ( !regcomp(&regex, " ?\\([^)]+\\)", 1) )
  {
    // Loop as long as we find a match in the string
    while ( !regexec(&regex, result, 2uLL, matches, 0) )
    {
      char *match_start = &result[matches[0].rm_so];
      char *match_end = &result[matches[0].rm_eo];
      
      // Calculate the length of the remaining string (including null terminator)
      size_t remaining_len = strlen(result) - matches[0].rm_eo + 1;
      
      // Overwrite the matched portion with the rest of the string
      memmove(match_start, match_end, remaining_len);
    }
    regfree(&regex);
  }
  
  return result;
}