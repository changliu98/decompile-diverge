void decrypt(char *string, int shift)
{
  int i = 0;
  for (i = 0; string[i] != '\0'; i++)
  {
    if (string[i] == '-')
      string[i] = ' ';
    else
    {
      string[i] = (string[i] - 97 + (shift % 26)) % 26 + 97;
    }
  }
}