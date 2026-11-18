#include <stdio.h>

#include <string.h>

void strip(char *str)
{
 if(str == NULL)
  return;

 int i, j;
 char *p = str;


 for(i=1; str[i] != '\0'; i++)
 {
  for(j=0; j<i; j++)
  {
   if(p[j] == str[i])
   {
    str[i] = -1;
    break;
   }
  }
 }





 int redun = 0, common = 0;
 for(i=1; str[i] != '\0'; i++)
 {
  if(str[i] != -1)
   continue;

  redun = i;
  while(str[i] == -1)
   i++;

  common = i;
  break;
 }


 if(redun == 0)
  return;




 while(str[common] != '\0')
 {
  if(str[common] == -1)
  {
   common++;
   continue;
  }
  str[redun++] = str[common];
  str[common++] = -1;
 }
 str[redun] = '\0';
}
