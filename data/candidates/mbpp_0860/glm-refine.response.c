const char *__cdecl func0(const char *str)
{
  regex_t reg;
  regmatch_t matches[1];
  int ret;

  // Compile the regular expression to match a string ending with an alphanumeric character.
  // REG_EXTENDED (1) is used to utilize extended POSIX regular expressions.
  ret = regcomp(&reg, "[a-zA-Z0-9]$", REG_EXTENDED);
  if (ret) {
    return "Error compiling regex";
  }

  // Execute the regular expression against the input string.
  // Note: Passing 1 match group is technically unnecessary since the regex has no capture groups,
  // but it is kept to preserve the exact semantics of the original binary.
  ret = regexec(&reg, str, 1, matches, 0);
  
  // Free the memory allocated by regcomp
  regfree(&reg);

  // regexec returns 0 on a successful match, and REG_NOMATCH (1) otherwise
  if (ret) {
    return "Discard";
  } else {
    return "Accept";
  }
}