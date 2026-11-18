static char *unmakemask (int mask, char *buff) {
  int i = 0;
  if (mask & LUA_MASKCALL) buff[i++] = 'c';
  if (mask & LUA_MASKRET) buff[i++] = 'r';
  if (mask & LUA_MASKLINE) buff[i++] = 'l';
  buff[i] = '\0';
  return buff;
}