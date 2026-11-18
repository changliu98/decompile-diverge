char *get_count(char **test_list, int size)
{
  int i; int j; int k; int len; int count = 0;
  char reversed[100];
  for (i = 0; i < size; i++)
  {
    for (j = i; j < size; j++)
    {
      len = strlen(test_list[i]);
      for (k = 0; k < len; k++)
      {
        reversed[k] = test_list[i][len - 1 - k];
      }
      reversed[len] = '\0';
      if (strcmp(test_list[j], reversed) == 0)
      {
        count++;
      }
    }
  }
  sprintf(get_count_result,"%d", count);
  return get_count_result;
}