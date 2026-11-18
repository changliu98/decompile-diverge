bool is_uletter(char c)
{
  if (c >= 'A')
    return c <= 'Z';
  return false;
}