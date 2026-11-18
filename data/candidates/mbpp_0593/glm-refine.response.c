char *__cdecl func0(const char *ip_str)
{
  size_t match_start;
  size_t curr_len;
  char *scan_ptr;
  char *result;
  char pattern[5]; 
  regmatch_t matches[1];
  regex_t regex;

  // Pattern matches a literal dot followed by one or more '0's (e.g., ".0", ".00")
  strcpy(pattern, "\\.[0]+");
  
  // Allocate memory for the resulting string
  result = (char *)malloc(strlen(ip_str) + 1);
  if (!result) return NULL; // Safety check for malloc failure
  
  // Compile the regex. Flag 1 corresponds to REG_EXTENDED
  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    free(result);
    return NULL;
  }
  
  // Copy the original IP string to the result buffer
  strcpy(result, ip_str);
  
  // Iteratively find and remove the pattern occurrences
  for (scan_ptr = result; !regexec(&regex, scan_ptr, 1, matches, 0); scan_ptr += match_start + 1)
  {
    curr_len = strlen(scan_ptr);
    match_start = matches[0].rm_so;
    
    // Overwrite the matched ".0+" sequence by shifting the remainder of the string left.
    // This effectively leaves a single '.' from the matched pattern and removes the '0's.
    memmove(
      &scan_ptr[match_start + 1], 
      &scan_ptr[matches[0].rm_eo], 
      curr_len - matches[0].rm_eo + 1
    );
  }
  
  regfree(&regex);
  return result;
}