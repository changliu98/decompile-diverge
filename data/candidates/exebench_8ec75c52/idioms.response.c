void strupr(char *str)
{
  for (; *str != '\0'; str++)
  {
    if (*str >= 'a' && *str <= 'z')
      *str -= 'a' - 'A';
  }
}