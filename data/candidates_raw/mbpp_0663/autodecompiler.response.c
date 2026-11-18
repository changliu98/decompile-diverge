int getModulo(int dividend, int divisor, int remainder)
{
 int output;
 int i = dividend;
 int j = 0;
 int max = -2147483648;

 while(1)
 {
  if(j > dividend)
   break;

  if((j % divisor) == remainder)
  {
   if(max < j)
    max = j;
  }

  j++;
 }

 if(max >= 0 && max <= dividend)
  output = max;
 else
  output = -1;

 return output;
}