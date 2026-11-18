const char *__cdecl func0(const char *text)
{
  regex_t regex;
  
  // REG_EXTENDED is typically defined as 1 in standard POSIX environments
  if (regcomp(&regex, "ab{3}", REG_EXTENDED))
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }

  int reti = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);

  if (reti == 0)
    return "Found a match!";
  else
    return "Not matched!";
}