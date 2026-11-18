// Function to check if the input string starts with '5'
_Bool func0(char *string)
{
  // Declare a regex object to hold the compiled pattern
  regex_t pattern;
  // Compile the regular expression pattern "^5" (matches strings starting with '5')
  if (regcomp(&pattern, "^5", 0) != 0) {
    // If compilation fails, print an error message and return false
    fprintf(stderr, "Could not compile regex\n");
    return false;
  }
  // Execute the compiled regex against the input string
  int match_status = regexec(&pattern, string, 0, NULL, 0);
  // Free the resources associated with the compiled regex
  regfree(&pattern);
  // Return true if the regex matched (result == 0), false otherwise
  return match_status == 0;
}