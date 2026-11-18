char *string_copy(char *dest, char *src)
{
  if (src == ((void *)0) || dest == ((void *)0))
    return ((void *)0);
  for (src, dest; *src != '\0'; src++, dest++)
    *dest = *src;
  *dest = '\0';
  return dest;
}