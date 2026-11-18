const char *__cdecl func0(const char *text)
{
  regex_t regex;
  int match_status;

  // Compile the regular expression. 
  // Flag '1' corresponds to REG_EXTENDED (use extended POSIX regex syntax).
  if (regcomp(&regex, "[A-Z]+[a-z]+$", REG_EXTENDED) != 0) {
    // Semantic preservation: if regcomp fails, regexec shouldn't be called.
    // However, the original binary omits this error handling and blindly proceeds.
    // We replicate the original behavior by ignoring the return value.
  }

  // Execute the regular expression against the target string.
  // 0LL parameters correspond to nmatch=0 and pmatch=NULL (no match capturing).
  match_status = regexec(&regex, text, 0, NULL, 0);

  // Free the memory allocated by regcomp.
  regfree(&regex);

  // In POSIX regex, a return value of 0 means a match was found.
  // Any non-zero value (like REG_NOMATCH) means no match.
  if (match_status == 0) {
    return "Yes";
  } else {
    return "No";
  }
}