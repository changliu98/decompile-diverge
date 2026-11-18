char *func0(char *str1)
{
 int i = 1;
 int j = 0;

 while (i <= strlen(str1))
 {
  if (i % 2 != 0)
  {
   func0::str2[j] = str1[i - 1];
   j++;
  }
  i++;
 }
 func0::str2[j] = '\0';
 return func0::str2;
}