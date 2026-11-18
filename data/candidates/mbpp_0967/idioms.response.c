char *func0(char *password)
{
  char *str = password;
  char vowels[] = "AEIOUaeiou";
  int i; int j;
  int count = 0;
  int found[10];
  memset(found, 0, sizeof(found));
  for (i = 0; str[i]; i++)
  {
    for (j = 0; j < 10; j++)
    {
      if (str[i] == vowels[j] && !found[j])
      {
        found[j] = 1;
        count++;
        break;
      }
    }
  }
  if (count >= 5)
    return "accepted";
  else
    return "rejected";
}