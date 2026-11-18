int func0(char *s)
{
 int n,i;
 char c;
 n=strlen(s);
 if(n<3)
  c=0;
 else
 {
  for(i=2;i*i<=n;i++)
  {
   if(n%i==0)
   {
    c=0;
    break;
   }
   else
    i++;
  }
  if(c!=0)
   c=1;
 }
 return (c==1);
}