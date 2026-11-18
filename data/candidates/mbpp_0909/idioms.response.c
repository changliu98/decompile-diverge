int func0(int num)
{
  int i; int j; int k; int len;
  char str[10]; char rev_str[10]; char temp;
  int num_int = num;
  for (i = num - 1; i > 0; i--)
  {
    sprintf(str, "%d", i);
    strcpy(rev_str, str);
    len = strlen(rev_str);
    for (j = 0; j < len / 2; j++)
    {
      temp = rev_str[j];
      rev_str[j] = rev_str[len - 1 - j];
      rev_str[len - 1 - j] = temp;
    }
    if (strcmp(str, rev_str) == 0)
    {
      return i;
    }
  }
  return 0;
}