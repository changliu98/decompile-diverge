void decrypt(char *str)
{
  while(*str)
  {
    if(*str != 'p' && *str != '\\' && *str != 'S')
      *str = *str ^ 15;
    str++;
  }
}