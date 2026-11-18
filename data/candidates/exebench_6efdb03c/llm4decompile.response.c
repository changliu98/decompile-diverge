void rev(char s[])
{
 int i,j,l;
 char c;
 for(l=0;s[l]!='\0';l++);
 for(i=0,j=l-1;i<l/2;i++,j--)
 {
  c=s[i];
  s[i]=s[j];
  s[j]=c;
 }
}