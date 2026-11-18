int sieve(int n)
{
 int i, j;
 int sum = 0;
 int arr[n+1];
 for(i = 0; i <= n; i++)
 {
  arr[i] = 0;
 }
 for(i = 2; i <= n; )
 {
  if(arr[i] == 0)
  {
   for(j = i; j <= n; j += i)
   {
    arr[j] += i;
   }
  }
  i++;
 }
 return arr[n];
}