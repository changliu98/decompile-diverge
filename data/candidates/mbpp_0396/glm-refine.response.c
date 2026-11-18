const char *__cdecl func0(const char *string)
{
  char err_msg[100];          // Buffer for regex error messages
  int ret;                    // Return code from regex operations
  regex_t regex;              // Compiled regex object
  const char *input_str;      // Copy of the input pointer

  input_str = string;

  // Compile the regex. Flag '1' corresponds to REG_EXTENDED.
  if (regcomp(&regex, "^[a-z]$|^([a-z]).*\\1$", REG_EXTENDED))
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Invalid";
  }
  else
  {
    // Execute the regex against the input string.
    // The 0LL arguments correspond to (size_t nmatch, regmatch_t pmatch[], int eflags).
    ret = regexec(&regex, input_str, 0, NULL, 0);

    if (ret)
    {
      // REG_NOMATCH is typically defined as 1
      if (ret == REG_NOMATCH)
      {
        regfree(&regex);
      }
      else
      {
        // Handle regex execution errors (e.g., invalid pattern state, out of memory)
        regerror(ret, &regex, err_msg, sizeof(err_msg));
        fprintf(stderr, "Regex match failed: %s\n", err_msg);
        regfree(&regex);
      }
      return "Invalid";
    }
    else
    {
      // Match found
      regfree(&regex);
      return "Valid";
    }
  }
}