const char *__cdecl func0(const char *string)
{
  regmatch_t matches[1]; // [rsp+8h] [rbp-68h] BYREF
  int ret; // [rsp+14h] [rbp-5Ch]
  const char *regex; // [rsp+18h] [rbp-58h]
  regex_t reg; // [rsp+20h] [rbp-50h] BYREF
  const char *stringa; // [rsp+60h] [rbp-10h]

  stringa = string;
  regex = "[a-zA-Z0-9]$";
  ret = regcomp(&reg, "[a-zA-Z0-9]$", 1);
  if ( ret )
    return "Error compiling regex";
  ret = regexec(&reg, stringa, 1uLL, matches, 0);
  regfree(&reg);
  if ( ret )
    return "Discard";
  else
    return "Accept";
}