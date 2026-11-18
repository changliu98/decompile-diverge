int btr(int n)
{
 int i=0, temp=n, sum=0;
 while(1)
 {
  if(temp>0)
  {
   if(i%2==1)
   {
    sum=sum|(1<<i);
   }
   i++;
   temp=temp>>1;
  }
  else
  {
   break;
  }
 }
 return (n|sum);
}