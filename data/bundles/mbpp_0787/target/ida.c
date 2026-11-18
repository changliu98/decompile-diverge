char *__cdecl func0(const char *text)
{
  int reti; // [rsp+Ch] [rbp-54h]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  const char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  if ( regcomp(&regex, "ab{3}", 1) )
  {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  else
  {
    reti = regexec(&regex, texta, 0LL, 0LL, 0);
    regfree(&regex);
    if ( reti )
      return "Not matched!";
    else
      return "Found a match!";
  }
}