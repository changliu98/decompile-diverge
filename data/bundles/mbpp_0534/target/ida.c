int __cdecl func0(const char *pattern, const char *text, int *start, int *end)
{
  int status; // [rsp+Ch] [rbp-74h]
  regmatch_t match; // [rsp+10h] [rbp-70h] BYREF
  regex_t regex; // [rsp+18h] [rbp-68h] BYREF
  int *enda; // [rsp+58h] [rbp-28h]
  int *starta; // [rsp+60h] [rbp-20h]
  const char *texta; // [rsp+68h] [rbp-18h]
  const char *patterna; // [rsp+70h] [rbp-10h]

  patterna = pattern;
  texta = text;
  starta = start;
  enda = end;
  if ( regcomp(&regex, pattern, 1) )
    return -1;
  status = regexec(&regex, texta, 1uLL, &match, 0);
  regfree(&regex);
  if ( status )
    return -1;
  *starta = match.rm_so;
  *enda = match.rm_eo;
  return 0;
}