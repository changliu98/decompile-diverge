char *__cdecl func0(const char *text)
{
  char word[100];
  regmatch_t match[1];
  regex_t regex;
  const char *current_text = text;

  // Compile regex to match words ending with "ly" (REG_EXTENDED = 1)
  if (regcomp(&regex, "\\w+ly", REG_EXTENDED) != 0)
  {
    printf("Could not compile regex\n");
    return NULL;
  }

  // Execute regex search
  if (regexec(&regex, current_text, 1, match, 0) != 0)
  {
    regfree(&regex);
    return NULL;
  }

  int start = match[0].rm_so;
  int end = match[0].rm_eo;
  int length = end - start;

  // Extract the matched word
  strncpy(word, &current_text[start], length);
  word[length] = '\0';

  // Format the output: "<start>-<end>: <word>"
  snprintf(func0_result, 100, "%d-%d: %s", start, end, word);

  regfree(&regex);
  return func0_result;
}