int func0(char *x, char *n)
{
 char num[101], den[101];
 int i, j, a, b, c, d;

 for (i = 0; x[i] != '/'; i++)
  num[i] = x[i];
 num[i] = '\0';
 a = atoi(num);

 for (i = i + 1, j = 0; x[i] != '\0'; i++, j++)
  den[j] = x[i];
 den[j] = '\0';
 b = atoi(den);

 for (i = 0; n[i] != '/'; i++)
  num[i] = n[i];
 num[i] = '\0';
 c = atoi(num);

 for (i = i + 1, j = 0; n[i] != '\0'; i++, j++)
  den[j] = n[i];
 den[j] = '\0';
 d = atoi(den);

 if ((a * c) % (b * d) == 0)
  return 1;
 else
  return 0;
}