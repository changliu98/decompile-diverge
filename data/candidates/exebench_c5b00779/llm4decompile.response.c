int Fibonacci_search(int *a,int n,int key)
{
 int F[13] = {1,1,2,3,5,8,13,21,34,55,89,144,233};
 int k = 0;
 int low = 1;
 int high = n;
 int mid;
 while(n >= F[k]-1)
  k++;
 while(n < F[k]-1)
  a[n++] = a[n-1];
 while(low <= high)
 {
  mid = low + F[k-1] - 1;
  if(key < a[mid])
  {
   high = mid - 1;
   k = k - 1;
  }
  else if(key > a[mid])
  {
   low = mid + 1;
   k = k - 2;
  }
  else
  {
   if(mid > n)
    return n;
   else
    return mid;
  }
 }
 return 0;
}