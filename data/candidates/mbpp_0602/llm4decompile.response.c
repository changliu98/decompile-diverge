char func0(char *str1)
{
 int i,j,len,count;
 len = strlen(str1);
 for(i=0;i<len;i++)
 {
  count = 0;
  for(j=0;j<=i;j++)
  {
   if(str1[j]==str1[i])
    count++;
  }
  if(count>1)
   return str1[i];
 }
 return '0';
}