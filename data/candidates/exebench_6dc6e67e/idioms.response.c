void copia(char *dest, char *src)
{
  while(*src)
    *dest++ = *src++;
  *dest = '\0';
}