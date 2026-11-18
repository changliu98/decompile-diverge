char *__cdecl func0(char **patterns, int pattern_n, char *text)
{
  int i; // [rsp+8h] [rbp-68h]
  regex_t regex; // [rsp+10h] [rbp-60h] BYREF
  char *texta; // [rsp+50h] [rbp-20h]
  int pattern_na; // [rsp+5Ch] [rbp-14h]
  char **patternsa; // [rsp+60h] [rbp-10h]

  patternsa = patterns;
  pattern_na = pattern_n;
  texta = text;
  for ( i = 0; i < pattern_na; ++i )
  {
    if ( regcomp(&regex, patternsa[i], 0) )
    {
      fprintf(stderr, "Could not compile regex\n");
      return "Not Matched!";
    }
    if ( !regexec(&regex, texta, 0LL, 0LL, 0) )
    {
      regfree(&regex);
      return "Matched!";
    }
    regfree(&regex);
  }
  return "Not Matched!";
}