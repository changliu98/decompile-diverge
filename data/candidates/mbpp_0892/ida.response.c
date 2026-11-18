char *__cdecl func0(const char *text)
{
  char *v1; // rax
  char *bufptr; // [rsp+8h] [rbp-68h]
  const char *cursor; // [rsp+10h] [rbp-60h]
  regmatch_t match; // [rsp+18h] [rbp-58h] BYREF
  regex_t regex; // [rsp+20h] [rbp-50h] BYREF
  const char *texta; // [rsp+60h] [rbp-10h]

  texta = text;
  cursor = text;
  bufptr = (char *)&func0_buffer;
  if ( regcomp(&regex, " +", 1) )
    return 0LL;
  while ( *cursor )
  {
    if ( regexec(&regex, cursor, 1uLL, &match, 0) )
    {
      strcpy(bufptr, cursor);
      break;
    }
    memcpy(bufptr, cursor, match.rm_so);
    v1 = &bufptr[match.rm_so];
    bufptr = v1 + 1;
    *v1 = 32;
    cursor += match.rm_eo;
  }
  regfree(&regex);
  return (char *)&func0_buffer;
}