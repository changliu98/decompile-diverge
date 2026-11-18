void word2string(unsigned int value, char *str)
{
  int i; int j;
  char *s = str;
  if (value == 0)
    strcpy(str, "zero");
  else
  {
    for (i = 0; i < 5; i++)
    {
      if (s + (value / word2string__smth[i]) == str)
        continue;
      s += (value / word2string__smth[i]) + '0';
      value = value % word2string__smth[i];
    }
    s += ' ';
  }
}