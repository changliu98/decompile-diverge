int wcsncpy_noescape(char *output, char *wildcard)
{
  while(*wildcard != '\0')
  {
    if(*wildcard == '\\')
    {
      wildcard++;
      if(*wildcard == '\0')
        break;
      if(output != ((void *)0))
        *output++ = *wildcard;
      wildcard++;
    }
    else if(*wildcard == '*' || *wildcard == '?' || *wildcard == '[' || *wildcard == ']')
      return 0;
    else
    {
      if(output != ((void *)0))
        *output++ = *wildcard;
      wildcard++;
    }
  }
  if(output != ((void *)0))
    *output = '\0';
  return 1;
}