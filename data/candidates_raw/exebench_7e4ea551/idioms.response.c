void strcpy(char *to, char *from)
{
  while ( *from != '\0')
    *to++ = *from++;
  *to = *from;
}