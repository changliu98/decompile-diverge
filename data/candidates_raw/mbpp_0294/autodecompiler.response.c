int max(int list[], int n)
{
 int i;
 int max = -2147483648;

 for (i = 0; ; i++)
 {
  if (i >= n)
   break;
  if (list[i] > max)
   max = list[i];
 }
 return max;
}