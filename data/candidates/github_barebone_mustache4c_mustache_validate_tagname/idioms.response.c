int mustache_validate_tagname(char *tagname, unsigned long tagname_len)
{
  unsigned long i;
  if (tagname_len == 1 && tagname[0] == '.')
    return 0;
  if (tagname[0] == '.' || tagname[tagname_len - 1] == '.')
    return -1;
  for (i = 0; i < tagname_len; i++) {
    if (tagname[i] == ' ' || tagname[i] == '\t' ||
        tagname[i] == '\v' || tagname[i] == '\f')
      return -1;
    if (tagname[i] == '.' && i + 1 < tagname_len &&
        tagname[i + 1] == '.')
      return -1;
  }
  return 0;
}