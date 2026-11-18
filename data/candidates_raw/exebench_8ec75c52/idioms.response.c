void to_upper(char *str)
{
  for (; *str != '\0'; str++)
  {
    if (*str >= 'a' && *str <= 'z')
      *str -= 'a' - 'A';
  }
}