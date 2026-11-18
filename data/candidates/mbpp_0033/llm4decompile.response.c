int func0(int N)
{
 int B_Number = 0;
 int i;
 int cnt = 0;
 int times;
 while(N)
 {
  times = 1;
  for(i = 0; i < cnt; i++)
  {
   times *= 10;
  }
  B_Number += (N%2)*times;
  N /= 2;
  cnt++;
 }
 return B_Number;
}