void func0(int *a, int n)
{
 int i, j, gap, temp;
 gap = n / 2;
 while(gap > 0)
 {
  for(i = gap; i < n; i++)
  {
   temp = a[i];
   j = i;
   while(j >= gap && a[j - gap] > temp)
   {
    a[j] = a[j - gap];
    j = j - gap;
   }
   a[j] = temp;
  }
  gap = gap / 2;
 }
}