int func0(long long int num)
{
 long long int i;
 int flag=0;
 for(i=2;i*i<=num;i++)
 {
  if(num%i==0)
  {
   flag=1;
   break;
  }
 }
 if(flag==0)
  return 1;
 else
  return 0;
}