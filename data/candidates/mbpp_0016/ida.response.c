char *__cdecl func0(const char *text)
{
  int reti; // [rsp+4h] [rbp-5Ch]
  regex_t regex; // [rsp+10h] [rbp-50h] BYREF
  const char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  regcomp(&regex, "^[a-z]+_[a-z]+$", 1);
  reti = regexec(&regex, texta, 0LL, 0LL, 0);
  regfree(&regex);
  if ( reti )
    return "Not matched!";
  else
    return "Found a match!";
}