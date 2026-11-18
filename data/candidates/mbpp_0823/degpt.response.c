char * func0(char *input_string,char *substring)
{
  char *match_position;
  regex_t regex;
  char regex_pattern [100];
  int match_result;
  char *result_message;
  
  // Check if sample is a substring of string
  match_position = strstr(input_string,substring);
  if (match_position == (char *)0x0) {
    // Sample is not a substring of string
    result_message = "entered string isnt a substring";
  }
  else {
    // Initialize pattern buffer to zero
    memset(regex_pattern,0,100);
    // Start pattern with '^' to match beginning of string
    regex_pattern[0] = '^';
    // Append sample to pattern
    strcat(regex_pattern,substring);
    // Compile the regex pattern
    regcomp((regex_t *)&regex,regex_pattern,0);
    // Execute the regex match against the string
    match_result = regexec((regex_t *)&regex,input_string,0,(regmatch_t *)0x0,0);
    // Free the compiled regex
    regfree((regex_t *)&regex);
    if (match_result == 0) {
      // String starts with the given substring
      result_message = "string starts with the given substring";
    }
    else {
      // String does not start with the given substring
      result_message = "string doesnt start with the given substring";
    }
  }
  return result_message;
}