static long argmatch(char *str, char *list[], void *val, unsigned long valsize)
{
  long i;
  unsigned long len = strlen(str);
  long match = -1;
  _Bool ambiguous = 0;
  for (i = 0; list[i]; i++) {
    if (strncmp(list[i], str, len) == 0) {
      if (strlen(list[i]) == len)
        return i;
      if (match == -1)
        match = i;
      else {
        if (val == ((void *)0))
          ambiguous = 1;
        else if (memcmp(((char *)val) + match * valsize, ((char *)val) + i * valsize, valsize) != 0)
          ambiguous = 1;
      }
    }
  }
  if (ambiguous)
    return -2;
  return match;
}