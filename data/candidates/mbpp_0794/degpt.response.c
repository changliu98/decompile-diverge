char * func0(char *text)
{
  regex_t compiled_regex; // Declare a regex object to hold the compiled regular expression
  char *result_message; // Pointer to store the result string

  // Compile the regular expression pattern "a.*?b$" with extended regex flag (1)
  if (regcomp(&compiled_regex, "a.*?b$", 1) == 0) {
    // Execute the compiled regex against the input text
    if (regexec(&compiled_regex, text, 0, NULL, 0) == 0) {
      result_message = "Found a match!"; // Set result to match message
    }
    else {
      result_message = "Not matched!"; // Set result to no-match message
    }
    regfree(&compiled_regex); // Free the memory allocated for the compiled regex
  }
  else {
    fprintf(stderr, "Could not compile regex\n"); // Print error message to stderr
    result_message = "Error"; // Set result to error message
  }
  return result_message; // Return the result string
}