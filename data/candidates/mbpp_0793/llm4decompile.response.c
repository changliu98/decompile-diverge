int func0(int arr[], int x, int n) {
 int low, high, mid, res;
 low = 0; high = n - 1; res = -1;
 while (low <= high) {
  mid = (low + high) / 2;
  if (x < arr[mid]) {
   high = mid - 1;
  } else if (x > arr[mid]) {
   low = mid + 1;
  } else {
   res = mid;
   low = mid + 1;
  }
 }
 return res;
}