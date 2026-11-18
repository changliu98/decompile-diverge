static size_t get_next_path(char *path, size_t pathlen, size_t *startpos, size_t *endpos)
{
 size_t ret;

 do {
  while (*startpos < pathlen && path[*startpos] != '\\') (*startpos)++;
  if (*startpos == pathlen) {
   ret = 0;
   goto out;
  }
  (*startpos)++;
  *endpos = *startpos + 1;
  do {
   while (*endpos < pathlen && path[*endpos] != '\\') (*endpos)++;
  } while (0);
  ret = *endpos - *startpos;
 } while (0);

out:
 return ret;
}