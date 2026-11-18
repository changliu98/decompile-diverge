int greatestPowerOfTwoDividing(int n)
{
 int i;
 int result = 0;

 for(i = n; i > 0; --i)
 {
  if((i & (i-1)) == 0)
  {
   result = i;
   break;
  }
 }

 return result;
}