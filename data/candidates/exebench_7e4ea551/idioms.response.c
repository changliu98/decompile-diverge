void inplace_strcpy(char *to, char *from)
{
  while ( *from != '\0')
    *to++ = *from++;
  *to = *from;
}