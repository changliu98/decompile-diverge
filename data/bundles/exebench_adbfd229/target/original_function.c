void sort(char str[])
{
 int i,j;
 char t;
 for(j=1;j<10;j++)
  for (i=0;(i<10 -j)&&(str[i]!='\0');i++)
   if(str[i]>str[i+1])
   {
    t=str[i];
    str[i]=str[i+1];
    str[i+1]=t;
   }
}