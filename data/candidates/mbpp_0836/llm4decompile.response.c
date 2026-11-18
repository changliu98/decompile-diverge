int func0(int a[], int size)
{
 int max_so_far = -2147483648;
 int max_ending_here = 0;
 int start = 0;
 int end = 0;
 int s = 0;
 int i = 0;
 while (i < size)
 {
  max_ending_here += a[i];
  if (max_so_far < max_ending_here)
  {
   max_so_far = max_ending_here;
   start = s;
   end = i;
  }
  if (max_ending_here < 0)
  {
   max_ending_here = 0;
   s = i + 1;
  }
  i++;
 }
 return (end - start + 1);
}