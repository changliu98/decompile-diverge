char most_frequent(char *str)
{
  int i;
  int len;
  int frequency[-1];
  char max_char = 0;
  int max_freq = 0;
  char *str1 = str;
  memset(frequency, 0, sizeof(frequency));
  for (len = strlen(str1); i = 0; i < len; i++)
  {
    if (++frequency[(int)(unsigned char)(str1[i])]>max_freq)
    {
      max_freq = frequency[(int)(unsigned char)(str1[i])];
      max_char = str1[i];
    }
  }
  return max_char;
}