int compter_mots(char *line, unsigned long *max_lenght)
{
  int words = 0;
  int gui = 0;
  unsigned long current_lenght = 0;
  unsigned long max_current = 0;
  char *p = strchr(line,'\0')-1;
  while(*p == ' ')
    {
      *p = '\0';
      --p;
    }
  for(p = line; *p == ' '; ++p);
  if(*p)
    ++words;
  for(; *p; ++p)
    {
      if(*p == '"' || *p == '\'')
        gui = !gui;
      else if(*p == ' ' && !gui)
        {
          if(current_lenght > max_current)
            max_current = current_lenght;
          current_lenght = 0;
          ++words;
          while(*p == ' ')
            ++p;
          --p;
        }
      else
        ++current_lenght;
    }
  if(current_lenght > max_current)
    max_current = current_lenght;
  *max_lenght = max_current;
  return words;
}