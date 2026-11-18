const char *__cdecl func0(const char *str)
{
  regex_t regex;
  const char *result;

  // Compile the regular expression.
  // REG_EXTENDED (1) | REG_NOSUB (8) = 9
  if (regcomp(&regex, "^[aeiouAEIOU][A-Za-z0-9_]*", 9) != 0) {
    return "Invalid";
  }

  // Execute the regular expression.
  // regexec returns 0 on a successful match, or REG_NOMATCH on failure.
  result = (regexec(&regex, str, 0, NULL, 0) == 0) ? "Valid" : "Invalid";

  regfree(&regex);
  return result;
}