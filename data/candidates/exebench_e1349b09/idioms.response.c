char *strcpy(char *dest, char *src)
{
  char *d = dest;
  do
  {
    *dest = *src;
    if (*dest++ == '\0')
      break;
  } while (1);
  return d;
}