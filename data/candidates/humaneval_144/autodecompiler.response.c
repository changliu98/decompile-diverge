int func0(char *frac1, char *frac2)
{
 int num1, num2, den1, den2;
 int i, j;
 char str1[100], str2[100];
 for(i = 0; ; i++)
 {
  if(frac1[i] != '/')
  {
   str1[i] = frac1[i];
  }
  else
  {
   str1[i] = '\0';
   num1 = atoi(str1);
   break;
  }
 }

 for(j = 0, i++; ; j++, i++)
 {
  if(frac1[i] == '\0')
  {
   str2[j] = '\0';
   den1 = atoi(str2);
   break;
  }
  str2[j] = frac1[i];
 }

 for(i = 0; ; i++)
 {
  if(frac2[i] != '/')
  {
   str1[i] = frac2[i];
  }
  else
  {
   str1[i] = '\0';
   num2 = atoi(str1);
   break;
  }
 }

 for(j = 0, i++; ; j++, i++)
 {
  if(frac2[i] == '\0')
  {
   str2[j] = '\0';
   den2 = atoi(str2);
   break;
  }
  str2[j] = frac2[i];
 }

 if((num1*num2) % (den1*den2) == 0)
  return 1;
 else
  return 0;
}