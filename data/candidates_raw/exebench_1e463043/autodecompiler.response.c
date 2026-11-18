int strcmp(char *str1, char *str2)
{
 int i;
 for(i = 0; ; i++)
 {
  if(str1[i] == 0 && str2[i] == 0)
   break;

  if(str1[i] >= 'a' && str1[i] <= '{')
   str1[i] -= 32;

  if(str2[i] >= 'a' && str2[i] <= '{')
   str2[i] -= 32;

  if(str1[i] == 0 || str2[i] == 0)
   break;
 }

 int return_value;
 for(i = 0; ; i++)
 {
  if(str1[i] == 0 && str2[i] == 0)
   return_value = 0;
  else if(str1[i] > str2[i])
   return_value = 1;
  else if(str1[i] < str2[i])
   return_value = -1;
  else
   continue;

  break;
 }

 return return_value;
}