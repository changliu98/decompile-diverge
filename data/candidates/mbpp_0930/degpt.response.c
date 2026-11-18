char * func0(char *text)
{
  regex_t compiled_regex; // Declare a regex object to hold the compiled regular expression
  char *result_message; // Pointer to store the result message
  
  // Compile the regular expression "ab*?" with REG_EXTENDED flag (1)
  if (regcomp(&compiled_regex, "ab*?", 1) == 0) {
    // Execute the compiled regex against the input text
    int match_result = regexec(&compiled_regex, text, 0, NULL, 0);
    // Free the resources associated with the compiled regex
    regfree(&compiled_regex);
    
    // Check the result of the regex execution
    if (match_result == 0) {
      // Match found
      result_message = "Found a match!";
    }
    else if (match_result == 1) {
      // No match found
      result_message = "Not matched!";
    }
    else {
      // An error occurred during matching
      result_message = "Regex match failed";
    }
  }
  else {
    // Error occurred during regex compilation
    result_message = "Error compiling regex";
  }
  // Return the result message
  return result_message;
}