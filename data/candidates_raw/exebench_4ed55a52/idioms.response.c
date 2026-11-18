void encrypt(char *text)
{
  int i = 0;
  while (text[i])
  {
    text[i++] += 5;
  }
}