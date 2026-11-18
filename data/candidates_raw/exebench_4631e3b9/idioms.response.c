int decrypt(char *text)
{
  while (*text)
  {
    *text = *text - 13;
    text++;
  }
  return 0;
}