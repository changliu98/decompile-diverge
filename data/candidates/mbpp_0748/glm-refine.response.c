void __cdecl func0(const char *str, char *result)
{
  char buffer[1024];
  regmatch_t matches[3];
  regex_t regex;
  char *cursor;

  // Compile a regular expression to match a lowercase letter followed by an uppercase letter
  // REG_EXTENDED (1) is used for extended regex syntax.
  regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
  
  // Copy the input string into a mutable buffer
  strcpy(buffer, str);
  cursor = buffer;
  
  // Initialize the result string
  result[0] = '\0';
  
  // Find all occurrences of the pattern
  while (regexec(&regex, cursor, 3, matches, 0) == 0)
  {
    // Append the string up to the end of the first capture group (the lowercase letter)
    strncat(result, cursor, matches[1].rm_eo);
    
    // Insert a space between the lowercase and uppercase letters
    strcat(result, " ");
    
    // Advance the cursor to the start of the second capture group (the uppercase letter)
    cursor += matches[2].rm_so;
  }
  
  // Append the remaining part of the string
  strcat(result, cursor);
  
  // Free the compiled regex
  regfree(&regex);
}