void strcpy(char *dest, char *src)
{
  char c;
  while (1)
  {
    c = *src;
    *dest = c;
    if (c == '\0')
      break;
    dest++;
    src++;
  }
}