int wc_unescape(char *output,char *wildcard)
{
  char *ptr;
  char *outptr;

  ptr = wildcard;
  outptr = output;

  while(*ptr != 0)
  {
    if(*ptr == '\\')
    {
      ptr++;
      if(*ptr != 0)
      {
        if(outptr != NULL)
        {
          *outptr = *ptr;
          outptr++;
        }
        ptr++;
      }
    }
    else if(*ptr == '*' || *ptr == '?' || *ptr == '[' || *ptr == ']')
    {
      return 0;
    }
    else
    {
      if(outptr != NULL)
      {
        *outptr = *ptr;
        outptr++;
      }
      ptr++;
    }
  }

  if(outptr != NULL)
  {
    *outptr = 0;
  }

  return 1;
}