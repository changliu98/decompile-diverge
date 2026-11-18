char *my_strcpy(char *dest, char *src)
{
  while ((*dest = *src) != '\0')
    {
      dest++;
      src++;
    }
  return (dest);
}