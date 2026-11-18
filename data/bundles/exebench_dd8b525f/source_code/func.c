
void reverse(char rline[])
{
 int i,j;
 char temp;

 for(i=0;rline[i]!='\0';++i)
  ;
 --i;
 if(rline[i]=='\n')
 --i;

 j = 0;

 while(j < i)
 {
  temp = rline[j];
  rline[j] = rline[i];
  rline[i] = temp;
  --i;
  ++j;
 }
}
