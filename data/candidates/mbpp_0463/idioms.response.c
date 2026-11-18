int func0(int a[], int n)
{
  int max_ending_here = 1;
  int min_ending_here = 1;
  int max_so_far = 0;
  int flag = 0;
  int i;
  for (i = 0; i < n; i++)
  {
    if (a[i] > 0)
    {
      max_ending_here = max_ending_here * a[i];
      int temp = a[i]*min_ending_here;
      if (temp < 1)
        min_ending_here = 1;
      else
        min_ending_here = temp;
      flag = 1;
    }
    else if (a[i] == 0)
    {
      max_ending_here = 1;
      min_ending_here = 1;
    }
    else
    {
      int temp = max_ending_here;
      int temp2 = a[i]*min_ending_here;
      if (temp2 < 1)
        max_ending_here = 1;
      else
        max_ending_here = temp2;
      min_ending_here = a[i]*temp;
    }
    if (max_so_far < max_ending_here)
      max_so_far = max_ending_here;
  }
  if (flag == 0 && max_so_far == 0)
    return 0;
  return max_so_far;
}