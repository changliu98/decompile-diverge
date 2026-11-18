char *mfile_name_concat(const char *dir, const char *base, char **base_in_result)
{
  char *result;
  char *p;
  size_t dirlen, baselen, dirbaselen;
  char sep;

  p = last_component(dir);
  dirlen = p - dir;
  baselen = base_len(p);
  dirbaselen = dirlen + baselen;

  baselen = strlen(base);

  if (dirlen == 0)
    {
      if (base[0] == '/')
        sep = '.';
      else
        sep = 0;
    }
  else
    {
      if (dir[dirlen - 1] == '/' || base[0] == '/')
        sep = 0;
      else
        sep = '/';
    }

  result = malloc(dirbaselen + baselen + (sep ? 1 : 0) + 1);
  if (!result)
    return NULL;

  memcpy(result, dir, dirlen);
  result[dirlen] = sep;
  p = result + dirlen + (sep ? 1 : 0);

  if (base_in_result)
    *base_in_result = p;

  memcpy(p, base, baselen);
  p[baselen] = 0;

  return result;
}