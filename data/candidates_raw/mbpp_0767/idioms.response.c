int countpairs(int a[], int n, int sum)
{
 int count = 0;
 int i = 0;
 for (i = 0; i < n; i++)
  for (int j = i + 1; j < n; j++)
   if (a[i] + a[j] == sum)
    count++;
 return count;
}