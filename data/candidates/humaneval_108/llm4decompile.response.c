int func0(int *n, int size)
{
 int i, num = 0;
 for (i = 0; i < size; i++)
 {
  if (n[i] > 0)
   num++;
  else
  {
   int sum = 0;
   int tmp = abs(n[i]);
   while (tmp >= 10)
   {
    sum += tmp % 10;
    tmp /= 10;
   }
   if (sum - tmp > 0)
    num++;
  }
 }
 return num;
}