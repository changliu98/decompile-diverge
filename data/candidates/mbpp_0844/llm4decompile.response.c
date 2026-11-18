int func0(int n, int k)
{
 int arr[n];
 int i, j, odd, even;

 odd = 1;
 even = 2;
 i = 0;
 while (odd <= n) {
  arr[i] = odd;
  i += 1;
  odd += 2;
 }
 while (even <= n) {
  arr[i] = even;
  i += 1;
  even += 2;
 }
 return arr[k-1];
}