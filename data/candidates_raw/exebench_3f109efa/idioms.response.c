void caesar(char *text, int offset)
{
  int i = 0;
  int j = 0;
  while (text[i] != '\0')
  {
    if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
    {
      for (j = 0; j < offset; j++)
      {
        if (text[i] == 'Z')
        {
          text[i] = 'A';
          text[i]--;
        }
        if (text[i] == 'z')
        {
          text[i] = 'a';
          text[i]--;
        }
        text[i]++;
      }
    }
    i++;
  }
}