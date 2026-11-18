void clearMarker(char *str, char cutchar)
{
  char *p = strchr(str, cutchar);
  if (p != ((void *)0))
    *p = '\0';
}