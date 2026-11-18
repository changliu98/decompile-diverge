char *regex_match(char **patterns, int pattern_n, char *text)
{
  int i;
  char *textp = text;
  char **patternsp = patterns;
  int pattern_np = pattern_n;
  for ( i = 0; i < pattern_np; i++ )
  {
    struct regex_t regex;
    if ( regcomp(&regex, patternsp[i], 0 ) != 0 )
    {
      fprintf(stderr, "Could not compile regex\n");
      return "Not Matched!";
    }
    if ( regexec(&regex, textp, 0, ((void *)0), 0 ) == 0 )
    {
      regfree(&regex);
      return "Matched!";
    }
    regfree(&regex);
  }
  return "Not Matched!";
}