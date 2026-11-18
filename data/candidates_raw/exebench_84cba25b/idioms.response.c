char *itoa(char *str, int i)
{
  str[0] = i / 91 + '!';
  str[1] = i % 91 + '!';
  return str + 2;
}