void strupr(char *str)
{
  while (*str)
  {
    if (*str >= 'a' && *str <= 'z')
      *str -= 'a' - 'A';
    str++;
  }
}