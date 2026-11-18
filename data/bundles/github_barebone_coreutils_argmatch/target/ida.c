ptrdiff_t __cdecl argmatch(const char *arg, const char *const *arglist, const void *vallist, size_t valsize)
{
  ptrdiff_t i; // [rsp+8h] [rbp-48h]
  bool ambiguous; // [rsp+17h] [rbp-39h]
  ptrdiff_t matchind; // [rsp+18h] [rbp-38h]
  size_t arglen; // [rsp+20h] [rbp-30h]

  arglen = strlen(arg);
  matchind = -1LL;
  ambiguous = 0;
  for ( i = 0LL; arglist[i]; ++i )
  {
    if ( !strncmp(arglist[i], arg, arglen) )
    {
      if ( strlen(arglist[i]) == arglen )
        return i;
      if ( matchind == -1 )
      {
        matchind = i;
      }
      else if ( !vallist || memcmp((char *)vallist + matchind * valsize, (char *)vallist + i * valsize, valsize) )
      {
        ambiguous = 1;
      }
    }
  }
  if ( ambiguous )
    return -2LL;
  else
    return matchind;
}