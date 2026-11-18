static long argmatch_exact(char *name, char *args[])
{
  long i = 0;
  while (args[i]) {
    if (strcmp(args[i], name) == 0)
      return i;
    i++;
  }
  return -1;
}