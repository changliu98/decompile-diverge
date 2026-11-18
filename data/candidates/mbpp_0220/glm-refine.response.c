char *__cdecl func0(const char *text, int n)
{
  regmatch_t pmatch[1];
  regex_t regex;
  int num_replacements;

  // Copy the initial text to the global buffer
  strcpy(func0_new_text, text);

  // Compile regex to match space, comma, or period
  // REG_EXTENDED (1) is used to enable extended regular expressions
  regcomp(&regex, "[ ,.]", REG_EXTENDED);

  // Replace the first 'n' occurrences of the matched characters with ':' (ASCII 58)
  for (num_replacements = 0; num_replacements < n; ++num_replacements)
  {
    if (regexec(&regex, func0_new_text, 1, pmatch, 0) != 0)
      break;

    func0_new_text[pmatch[0].rm_so] = ':';
  }

  regfree(&regex);
  return func0_new_text;
}