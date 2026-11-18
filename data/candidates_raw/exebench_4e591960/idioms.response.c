void str2int(char *str)
{
  while (*str)
    *str++ -= '0';
}