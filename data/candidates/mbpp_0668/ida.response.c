char *__cdecl func0(char *string, const char *charToReplace)
{
  size_t v2; // rax
  const char *src; // [rsp+10h] [rbp-90h]
  size_t pos; // [rsp+18h] [rbp-88h]
  const char *result; // [rsp+20h] [rbp-80h]
  size_t offset; // [rsp+28h] [rbp-78h]
  regmatch_t match; // [rsp+30h] [rbp-70h] BYREF
  char pattern[10]; // [rsp+3Eh] [rbp-62h] BYREF
  regex_t regex; // [rsp+48h] [rbp-58h] BYREF
  const char *charToReplacea; // [rsp+88h] [rbp-18h]
  char *stringa; // [rsp+90h] [rbp-10h]

  stringa = string;
  charToReplacea = charToReplace;
  sprintf(pattern, "%s{2,}", charToReplace);
  if ( regcomp(&regex, pattern, 1) )
    return 0LL;
  offset = 0LL;
  result = strdup(stringa);
  while ( !regexec(&regex, &result[offset], 1uLL, &match, 0) )
  {
    pos = match.rm_so + offset;
    src = &result[pos + match.rm_eo - match.rm_so];
    v2 = strlen(result);
    memmove((void *)&result[pos + 1], src, match.rm_so + v2 - pos - match.rm_eo + 1);
    offset = pos + 1;
  }
  regfree(&regex);
  return (char *)result;
}