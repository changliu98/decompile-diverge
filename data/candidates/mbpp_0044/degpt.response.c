char * func0(char *input_string)
{
  regex_t compiled_regex; // Declare a regex object to hold the compiled regular expression
  char *result_message; // Pointer to store the result message

  // Compile the regular expression pattern "^[[:alnum:]_]+" with extended regex flag (1)
  // The pattern matches strings starting with one or more alphanumeric characters or underscores
  if (regcomp((regex_t *)&compiled_regex,"^[[:alnum:]_]+",1) == 0) {
    // Free the compiled regex pattern to prevent memory leaks
    regfree((regex_t *)&compiled_regex);
    // Execute the regex against the input text
    // Note: The regex was freed before execution, which is likely a bug
    if (regexec((regex_t *)&compiled_regex,input_string,0,(regmatch_t *)0x0,0) == 0) {
      result_message = "Found a match!"; // Set result message if match is found
    }
    else {
      result_message = "Not matched!"; // Set result message if no match is found
    }
  }
  else {
    result_message = "Regex compilation error"; // Set error message if regex compilation fails
  }
  return result_message; // Return the result message
}