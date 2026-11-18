char *path_join(char *dir, char *base, char **base_in_result)
{
  char *dirbase = last_component(dir);
  unsigned long dirbaselen = base_len(dirbase);
  unsigned long dirlen = dirbaselen + (dirbase - dir);
  unsigned long baselen = strlen(base);
  char sep = '\0';
  if (dirbaselen == 0)
    if (base[0] == '/')
      sep = '.';
  else
    sep = '/';
  else
    if (dirbase[dirbaselen - 1] != '/' && base[0] != '/')
      sep = '/';
  char *res = malloc(dirlen + (sep != '\0') + baselen + 1);
  if (res == ((void *)0))
    return ((void *)0);
  memcpy(res, dir, dirlen);
  res[dirlen] = sep;
  char *base_in_res = res + dirlen + (sep != '\0');
  if (base_in_result != ((void *)0))
    *base_in_result = base_in_res;
  memcpy(base_in_res, base, baselen);
  base_in_res[baselen] = '\0';
  return res;
}