char heaviestCharacter (const char *string)
{
  int frequencyTable[256];
  int i, max = -1, length;
  char heaviestChar = '\0';

  memset(frequencyTable, 0, sizeof(int) * 256);

  length = strlen(string);
  for (i = 0; i < length; i++)
  {
    frequencyTable[(int) string[i]]++;
  }

  for (i = 0; i < length; i++)
  {
    if (frequencyTable[(int) string[i]] > max)
    {
      max = frequencyTable[(int) string[i]];
      heaviestChar = string[i];
    }
  }

  return heaviestChar;
}