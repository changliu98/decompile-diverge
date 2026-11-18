int func0(int x, int y)
{
 int i, result, temp;
 i = 1;
 result = 0;

 while(1)
 {
  if((i <= x) && (result < 100))
  {
   if(i == x)
   {
    result = 1;
    break;
   }
   else
   {
    i = i * y;
    result++;
   }
  }
  else
  {
   result = 0;
   break;
  }
 }

 return result;
}