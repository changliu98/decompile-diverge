char *__cdecl func0(char *string, const char *charToReplace)
{
  size_t str_len; // v2
  const char *src; 
  size_t match_pos; // pos
  char *result; 
  size_t offset; 
  regmatch_t match; 
  char pattern[10]; 
  regex_t regex; 

  // Construct a regex pattern like "X{2,}" to match 2 or more consecutive characters
  sprintf(pattern, "%s{2,}", charToReplace);
  
  // REG_EXTENDED (1) is used to support the {2,} syntax
  if (regcomp(&regex, pattern, REG_EXTENDED))
    return NULL;

  offset = 0;
  result = strdup(string);
  
  // Loop while we find matches in the remaining part of the string
  while (!regexec(&regex, &result[offset], 1, &match, 0))
  {
    // Calculate the absolute position of the start of the match
    match_pos = match.rm_so + offset;
    
    // Pointer to the remainder of the string right after the matched sequence
    src = &result[match_pos + match.rm_eo - match.rm_so];
    
    // Get the total length of the current string
    str_len = strlen(result);
    
    // Shift the remainder of the string leftwards to overwrite the extra characters.
    // This effectively collapses the matched sequence (e.g., "////") into a single character.
    memmove(&result[match_pos + 1], src, match.rm_so + str_len - match_pos - match.rm_eo + 1);
    
    // Move the offset past the single character we kept, to avoid infinite loops and continue searching
    offset = match_pos + 1;
  }
  
  regfree(&regex);
  return result;
}