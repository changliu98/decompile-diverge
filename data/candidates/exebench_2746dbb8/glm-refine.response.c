void __cdecl uc(char *str)
{
  while (*str)
  {
    if (*str >= 'a' && *str <= 'z')
      *str -= 'a' - 'A'; // or *str -= 32;
    ++str;
  }
}