char *unmakemask(int mask, char *line)
{
  int i = 0;
  if (mask & LUA_MASKCALL) line[i++] = 'c';
  if (mask & LUA_MASKRET) line[i++] = 'r';
  if (mask & LUA_MASKLINE) line[i++] = 'l';
  line[i] = '\0';
  return line;
}