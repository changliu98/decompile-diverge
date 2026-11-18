void squeeze_alt(char s1[], char s2[])
{
 int i,j,k;
 int flag=0;
 for(k=0,i=0;s1[i]!='\0';i++)
 {
  for(j=0;s2[j]!='\0'||flag==1;j++)
  {
   if(s1[i]==s2[j])
   {
    flag=1;
   }
  }
  if(flag==0)
  {
   s1[k++]=s1[i];
  }
  else
  {
   flag=0;
  }
 }
 s1[k]='\0';
}