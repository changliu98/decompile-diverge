char *
func0 (char *test_str)
{
  int i = 0, j = 0, k = 0;
  char dig[1024];

  while (test_str[i] != '\0')
    {
      if (test_str[i] >= '0' && test_str[i] <= '9')
 dig[j++] = test_str[i];
      else
 func0::res[k++] = test_str[i];

      i++;
    }

  dig[j] = '\0';
  func0::res[k] = '\0';

  strcat (func0::res, dig);

  return func0::res;
}