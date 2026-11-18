const char *__cdecl func0(const char *text)
{
  regex_t regex;
  const char *match_result;

  // Compile the regular expression "ab{2,3}" with the REG_EXTENDED flag (1)
  if (regcomp(&regex, "ab{2,3}", REG_EXTENDED) != 0) {
    // Note: The original binary omitted error handling for regcomp.
    // If compilation fails, regexec might behave unpredictably.
  }

  // Execute the regex against the input text
  // Returns 0 on match, REG_NOMATCH on failure
  if (regexec(&regex, text, 0, NULL, 0) == 0)
    match_result = "Found a match!";
  else
    match_result = "Not matched!";

  regfree(&regex);
  return match_result;
}