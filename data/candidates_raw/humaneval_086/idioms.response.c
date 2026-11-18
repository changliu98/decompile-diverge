char *sortString(char *str)
{
  int i; int j; int k;
  char temp;
  int len = strlen(str);
  char *out = (char *)malloc((len + 2) * sizeof(char));
  int out_index = 0;
  int current_index = 0;
  char current[50];
  for (i = 0; i <= len; i++)
  {
    if (str[i] == ' ' || str[i] == '\0')
    {
      for (j = 0; j < current_index - 1; j++)
      {
        for (k = j + 1; k < current_index; k++)
        {
          if (current[j] > current[k])
          {
            temp = current[j];
            current[j] = current[k];
            current[k] = temp;
          }
        }
      }
      if (out_index > 0)
      {
        out[out_index++] = ' ';
      }
      for (k = 0; k < current_index; k++)
      {
        out[out_index++] = current[k];
      }
      current_index = 0;
    }
    else
    {
      current[current_index++] = str[i];
    }
  }
  out[out_index] = '\0';
  return out;
}