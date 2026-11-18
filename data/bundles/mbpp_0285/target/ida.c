char *__cdecl func0(const char *text)
{
  const char *match_result; // [rsp+8h] [rbp-58h]
  regex_t regex; // [rsp+18h] [rbp-48h] BYREF
  const char *texta; // [rsp+58h] [rbp-8h]

  texta = text;
  regcomp(&regex, "ab{2,3}", 1);
  if ( regexec(&regex, texta, 0LL, 0LL, 0) )
    match_result = "Not matched!";
  else
    match_result = "Found a match!";
  regfree(&regex);
  return (char *)match_result;
}