void hashname(char *name, long *hash, long *len)
{
  char *cp = strrchr(name, '/');
  if (cp)
    cp++;
  else
    cp = name;
  *len = 0;
  *hash = 0;
  while (*cp) {
    *hash = *hash * 33;
    *hash += *cp++;
    (*len)++;
  }
}