void dummyfunc(char *str)
{
 int i = 0;
 char gb[] = "Goodbye";
 while (1)
 {
  if (str[i] == '\0')
  {
   break;
  }
  str[i] = gb[i];
  i++;
 }
}