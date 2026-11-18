char **func0(char *str)
{
  int count = 1;
  char *ptr = str;
  for ( ; *ptr; ++ptr )
    if ( *ptr == ' ' )
      ++count;
  char **list = (char **)malloc((count + 1)*sizeof(char *));
  if ( !list )
    return ((void *)0);
  char *strcopy = strdup(str);
  if ( !strcopy )
  {
    free(list);
    return ((void *)0);
  }
  int i = 0;
  char *token = strtok(strcopy," ");
  for ( ; token != ((void *)0); token = strtok(((void *)0), " ") )
  {
    list[i++] = strdup(token);
  }
  list[i] = ((void *)0);
  free(strcopy);
  return list;
}