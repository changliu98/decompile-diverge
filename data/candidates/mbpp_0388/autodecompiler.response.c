int func0(int n)
{
 int power = 0;
 int i = n;

 while (1)
 {
  if (i <= 0) break;
  if ((i & (i - 1)) == 0)
  {
   power = i;
   break;
  }
  else
  {
   i--;
  }
 }

 return power;
}