int set_filename(char *to, char *from)
{
  char *to_name = to;
  char *from_name = from;
  while(*from_name)
  {
    if(*from_name == '/')
    {
      *to_name = '\0';
      return 2;
    }
    *to_name = *from_name;
    to_name++;
    from_name++;
  }
  *to_name = '\0';
  return 1;
}