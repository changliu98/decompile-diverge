char *my_strcpy(char *s1, char *s2)
{
  char *s = s1;
  for (;;)
    switch (*s1++ = *s2++) {
    case '\0':
      return s;
    }
}