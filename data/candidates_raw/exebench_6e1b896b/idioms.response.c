void strcut(char *str, char c)
{
 char *p = strchr(str, c);
 if (p != ((void *)0))
  *p = '\0';
}