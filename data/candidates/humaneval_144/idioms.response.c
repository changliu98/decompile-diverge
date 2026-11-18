int func0(char *a, char *b)
{
  char num[100]; char den[100];
  int i = 0; int j = 0;
  int a1 = 0; int a2 = 0;
  int b1 = 0; int b2 = 0;
  for (i = 0; a[i] != '/'; i++)
    num[i] = a[i];
  num[i] = '\0';
  a1 = atoi(num);
  for (i = 0, j = 0; a[i] != '\0'; i++, j++)
    den[j] = a[i];
  den[j] = '\0';
  a2 = atoi(den);
  for (i = 0; b[i] != '/'; i++)
    num[i] = b[i];
  num[i] = '\0';
  b1 = atoi(num);
  for (i = 0, j = 0; b[i] != '\0'; i++, j++)
    den[j] = b[i];
  den[j] = '\0';
  b2 = atoi(den);
  if (a1 * b1 % (a2 * b2) == 0)
    return 1;
  return 0;
}