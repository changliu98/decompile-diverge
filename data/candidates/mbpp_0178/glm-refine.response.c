char *__cdecl func0(char **patterns, int pattern_n, char *text)
{
  regex_t regex;
  int i;

  // Iterate through each regex pattern in the array
  for ( i = 0; i < pattern_n; ++i )
  {
    // Compile the regular expression
    if ( regcomp(&regex, patterns[i], 0) )
    {
      fprintf(stderr, "Could not compile regex\n");
      return "Not Matched!";
    }

    // Execute the regular expression against the text
    if ( !regexec(&regex, text, 0LL, 0LL, 0) )
    {
      regfree(&regex);
      return "Matched!";
    }
    
    regfree(&regex);
  }
  
  return "Not Matched!";
}