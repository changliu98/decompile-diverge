char *func0(char *str)
{
 int j = 0;
 int length = strlen(str);
 int i = 0;

 while(1)
 {
  if(i >= length)
  {
   str[j] = '\0';
   break;
  }
  switch(str[i])
  {
   case ' ': break;
   default : str[j++] = str[i];
  }
  i++;
 }
 return str;
}