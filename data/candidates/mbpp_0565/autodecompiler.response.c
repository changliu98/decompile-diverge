char *func0(char *str1, char *str2)
{
 int len = strlen(str1);
 int i = 0;
 while(1)
 {
  if(i < len)
  {
   str2[i] = str1[i];
   i++;
  }
  else
  {
   str2[len] = '\0';
   return str2;
  }
 }
}