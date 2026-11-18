int func0(int arr[], int n)
{
 int max_ending_here = 1;
 int min_ending_here = 1;
 int max_so_far = 0;
 int flag = 0;
 int i;
 for (i = 0; i < n; i++)
 {
  if (arr[i] > 0)
  {
   max_ending_here = max_ending_here * arr[i];
   min_ending_here = ((min_ending_here * arr[i]) > (1) ? (1) : (min_ending_here * arr[i]));
   flag = 1;
  }
  else if (arr[i] < 0)
  {
   int temp = max_ending_here;
   max_ending_here = ((min_ending_here * arr[i]) > (1) ? (min_ending_here * arr[i]) : (1));
   min_ending_here = temp * arr[i];
  }
  else
  {
   max_ending_here = 1;
   min_ending_here = 1;
  }
  if (max_so_far < max_ending_here)
   max_so_far = max_ending_here;
 }
 if (flag == 0 && max_so_far == 0)
  return 0;
 return max_so_far;
}