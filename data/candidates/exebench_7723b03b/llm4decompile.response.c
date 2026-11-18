void sort(char *str)
{
 int i,j;
 char temp;
 for(i=0;str[i+1]!='\0';i++)
 {
  temp=str[i+1];
  for(j=i;str[j]>temp && j>0;j--)
  {
   str[j+1]=str[j];
  }
  str[j+1]=temp;
 }
}