int func0(int n)
{
 int i = 0;
 while(1)
 {
  if(n == 0) return i;
  n = n/10;
  i++;
 }
}