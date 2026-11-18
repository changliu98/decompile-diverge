int func0(int n)
{
 int power = 0;
 int temp_n = n;
 int i = 0;

 if((n & (n + 1)) == 0)
 {
  return n;
 }

 while(1)
 {
  if(temp_n == 0)
  {
   break;
  }
  if(temp_n & 1)
  {

  }
  else
  {
   power = i;
  }
  i++;
  temp_n = temp_n >> 1;
 }

 return (n | (1 << power));
}