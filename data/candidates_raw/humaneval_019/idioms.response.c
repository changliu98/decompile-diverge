char *expand(char *number)
{
  char *p = number;
  int count[10];
  char *numto[10];
  char current[6];
  int i; int j; int k;
  int index = 0;
  memset(count, 0, sizeof(int) * 10);
  memcpy(numto, numto1, sizeof(char *) * 10);
  if (*p != '\0')
  {
    do
    {
      for (i = 0; (current[i] = (i < (int)strlen(p)) ? p[i] : '\0') != '\0'; i++)
      {
      }
      for (j = 0; j < 10; j++)
      {
        if (strcmp(current, numto[j]) == 0)
        {
          count[j]++;
          break;
        }
      }
      p += i + 1;
    } while (*(p - 1) != '\0');
  }
  for (i = 0; i < 10; i++)
  {
    for (j = 0; j < count[i]; j++)
    {
      for (k = 0; numto[i][k] != '\0'; k++)
      {
        expand_out[index++] = numto[i][k];
      }
      expand_out[index++] = ' ';
    }
  }
  if (index > 0)
  {
    expand_out[index - 1] = '\0';
  }
  else
  {
    expand_out[0] = '\0';
  }
  return expand_out;
}