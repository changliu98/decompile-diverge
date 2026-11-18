int func0(int *a, int n)
{
 int i, min = 2147483647;
 for(i = 0; ; i++)
 {
  if(i >= n) break;
  if(a[i] < min) min = a[i];
 }
 return min;
}