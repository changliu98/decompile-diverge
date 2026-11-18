char *func0(char *str1)
{
 int i,j;
 for(i=0,j=0; str1[i]!='\0'; i++)
 {
  if(str1[i]<'a' || str1[i]>'z')
  {
   func0::result[j]=str1[i];
   j++;
  }
 }
 func0::result[j]='\0';
 return func0::result;
}