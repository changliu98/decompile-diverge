int lcm(int num1,int num2)
{
 int i;
 if(num1>num2)
 {
  i=num1;
 }
 else
 {
  i=num2;
 }
 while(1)
 {
  if(i%num1==0 && i%num2==0)
  {
   return i;
  }
  i++;
 }
}