int func0(char *strr)
{
 int sum = 0;
 int i = 0;
 for (i = 0; strr[i]; i++)
  sum += (strr[i] - 'a') + 1;
 if (sum % 26 == 0)
  return 'z';
 else
  return (sum % 26) + 'a'-1;
}