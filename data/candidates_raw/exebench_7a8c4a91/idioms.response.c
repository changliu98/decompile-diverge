void str_remove(char *str, char *exclude)
{
  char *s = str;
  char *d = str;
  char *e = exclude;
  char found;
  char exclude_is_null;
  while (*s)
  {
    e = exclude;
    do
    {
      found = *s == *e;
      e++;
      exclude_is_null = *e == '\0';
    } while (found & exclude_is_null);
    if (!found)
    {
      *d = *s;
      d++;
    }
    s++;
  }
  *d = '\0';
}