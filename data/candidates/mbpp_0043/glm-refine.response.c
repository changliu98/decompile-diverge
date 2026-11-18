char *__cdecl func0(const char *text)
{
  char errorMessage[100];
  regex_t regex;
  const char *patterns = "^[a-z]+_[a-z]+$";
  int ret;

  // Compile regex with REG_EXTENDED (flag = 1)
  if (regcomp(&regex, patterns, REG_EXTENDED))
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Compilation error";
  }

  // Execute regex against input text (no match capture)
  ret = regexec(&regex, text, 0, NULL, 0);

  if (ret == 0)
  {
    regfree(&regex);
    return "Found a match!";
  }

  if (ret == REG_NOMATCH)  // regexec returns 1 when no match
  {
    regfree(&regex);
    return "Not matched!";
  }

  // Any other non-zero return code indicates an error
  regerror(ret, &regex, errorMessage, sizeof(errorMessage));
  fprintf(stderr, "Regex match failed: %s\n", errorMessage);
  regfree(&regex);
  return "Error occurred";
}