int func0(int n)
{
 int tmp;
 int cnt = 0;
 int i = 0;
 while(1)
 {
  if(i >= n)
   break;
  if(!(i%11) || !(i%13))
  {
   tmp = i;
   while(tmp > 0)
   {
    if(tmp%10 == 7)
     cnt++;
    tmp /= 10;
   }
  }
  i++;
 }
 return cnt;
}