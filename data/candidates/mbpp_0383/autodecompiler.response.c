int func0(int num)
{
 int temp, cnt = 0, compNum = 0;
 temp = num;

 while(1)
 {
  if(temp > 0)
  {
   if(cnt % 2 == 0)
   compNum |= (1 << cnt);
   cnt++;
   temp >>= 1;
  }
  else
   break;
 }

 return (num ^ compNum);
}