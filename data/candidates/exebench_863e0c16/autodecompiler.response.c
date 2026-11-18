void reverse(char s[])
{
 int i,j;
 char c;

 for(j=0;1;++j)
  if(s[j]=='\0'||s[j]=='\n')
   break;
 --j;
 for(i=0;i<j;++i,--j) {
  c=s[i];
  s[i]=s[j];
  s[j]=c;
 }
}