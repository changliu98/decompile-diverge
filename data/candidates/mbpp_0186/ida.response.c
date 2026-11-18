char *__cdecl func0(const char *text, const char *pattern)
{
  int reti; // [rsp+4h] [rbp-5Ch]
  regex_t regex; // [rsp+8h] [rbp-58h] BYREF
  const char *patterna; // [rsp+48h] [rbp-18h]
  const char *texta; // [rsp+50h] [rbp-10h]

  texta = text;
  patterna = pattern;
  if ( regcomp(&regex, pattern, 0) )
    return "Regex compilation failed!";
  reti = regexec(&regex, texta, 0LL, 0LL, 0);
  regfree(&regex);
  if ( reti )
    return (char *)&unk_201E;
  else
    return "Matched!";
}