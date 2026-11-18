int my_strnatcmp(char *str1, int len1, char *str2, int len2)
{
  char num1[10];
  char num2[10];
  int i; int j; int is12;
  int len1a; int len2a;
  memset(num1, '\0', sizeof(num1));
  memset(num2, '\0', sizeof(num2));
  is12 = 0;
  j = 0;
  for (i = 0; str1[i]; i++)
  {
    if (((*__ctype_b_loc ())[(int) ((str1[i]))] & (unsigned short) _ISdigit))
    {
      if (is12)
      {
        num2[j++] = str1[i];
      }
      else
      {
        num1[j++] = str1[i];
      }
    }
    else
    {
      if (!is12 && j > 0)
      {
        is12 = 1;
        j = 0;
      }
    }
  }
  len1a = len1;
  len1a -= atoi(num1);
  len2a = len2 - atoi(num2);
  return (len1a - len2a);
}