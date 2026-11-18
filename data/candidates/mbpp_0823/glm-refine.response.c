const char *__cdecl func0(const char *str, const char *prefix)
{
  char pattern[100];
  regex_t regex;
  int result;

  // Check if the prefix exists anywhere in the string
  if (!strstr(str, prefix))
    return "entered string isnt a substring";

  // Construct a regex pattern to match the start of the string (e.g., "^prefix")
  memset(pattern, 0, sizeof(pattern));
  pattern[0] = '^';
  strcat(pattern, prefix);

  // Compile and execute the regex
  regcomp(&regex, pattern, 0);
  result = regexec(&regex, str, 0, NULL, 0);
  regfree(&regex);

  // Evaluate the regex match result
  if (result)
    return "string doesnt start with the given substring";
  else
    return "string starts with the given substring";
}