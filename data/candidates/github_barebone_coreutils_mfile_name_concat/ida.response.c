char *__cdecl mfile_name_concat(const char *dir, const char *base, char **base_in_result)
{
  char *p; // [rsp+18h] [rbp-58h]
  char *p_concat; // [rsp+20h] [rbp-50h]
  char sep; // [rsp+2Fh] [rbp-41h]
  size_t baselen; // [rsp+30h] [rbp-40h]
  size_t dirlen; // [rsp+38h] [rbp-38h]
  size_t dirbaselen; // [rsp+40h] [rbp-30h]
  char *dirbase; // [rsp+48h] [rbp-28h]

  dirbase = last_component(dir);
  dirbaselen = base_len(dirbase);
  dirlen = dirbaselen + dirbase - dir;
  baselen = strlen(base);
  sep = 0;
  if ( dirbaselen )
  {
    if ( dirbase[dirbaselen - 1] != 47 && *base != 47 )
      sep = 47;
  }
  else if ( *base == 47 )
  {
    sep = 46;
  }
  p_concat = (char *)malloc(baselen + (sep != 0) + dirlen + 1);
  if ( !p_concat )
    return 0LL;
  memcpy(p_concat, dir, dirlen);
  p_concat[dirlen] = sep;
  p = &p_concat[dirlen + (sep != 0)];
  if ( base_in_result )
    *base_in_result = p;
  memcpy(p, base, baselen);
  p[baselen] = 0;
  return p_concat;
}