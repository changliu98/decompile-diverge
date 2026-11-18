char *strcpy(char *dest, char *src)
{
  char *d = dest;
  do
    *d++ = *src++;
  while ( *src != '\0' );
  return dest;
}