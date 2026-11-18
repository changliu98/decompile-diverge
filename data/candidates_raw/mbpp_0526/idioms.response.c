char *to_camel_case(char *str)
{
  char *ret = ((void *)0);
  unsigned long len = strlen(str);
  if (ret = (char *)malloc((len + 1) * sizeof(char)))
  {
    if (len > 0)
    {
      ret[0] = toupper(str[0]);
      for (unsigned long i = 1; i < len; i++)
        ret[i] = tolower(str[i]);
      ret[len - 1] = toupper(ret[len - 1]);
      ret[len] = '\0';
    }
  }
  else
    return ((void *)0);
  return ret;
}