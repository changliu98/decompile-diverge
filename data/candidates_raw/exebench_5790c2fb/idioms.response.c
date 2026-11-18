void strcpy(char *dest, char *src)
{
  char c;
  while ((c = *src) != '\0')
  {
    *dest = c;
    src++;
    dest++;
  }
}