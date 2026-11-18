char *func0(char *str1, char *str2)
{
 int i;
 int j;

 j = 0;
 for (i = 0; ; ++i)
 {
  if (str1[i] == 0)
   break;

  if (str1[i] == ' ')
  {
   func0_str2[j++] = str2[0];
  }
  else
  {
   func0_str2[j++] = str1[i];
  }
 }

 func0_str2[j] = 0;

 return func0_str2;
}