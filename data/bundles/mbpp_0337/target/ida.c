char *__cdecl func0(const char *text)
{
  regmatch_t matches[1]; // [rsp+0h] [rbp-60h] BYREF
  char *patterns; // [rsp+8h] [rbp-58h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  const char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  patterns = "\\w+\\S*$";
  if ( regcomp(&regex, "\\w+\\S*$", 1) )
    return "Regex compilation failed";
  if ( regexec(&regex, texta, 1uLL, matches, 0) )
  {
    regfree(&regex);
    return "Not matched!";
  }
  else
  {
    regfree(&regex);
    return "Found a match!";
  }
}