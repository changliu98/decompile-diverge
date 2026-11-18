int __cdecl endGB(char *s, int *addend)
{
  bool v3; // [rsp+Fh] [rbp-11h]

  *addend = 0;
  v3 = 1;
  if ( !strstr(s, "//") )
    return strstr(s, "LOCUS") == s;
  return v3;
}