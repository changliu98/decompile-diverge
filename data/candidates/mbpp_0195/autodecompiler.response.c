int func0(int x[], int n, int len) {
 int low, mid, high;
 low = 0;
 high = len - 1;
 int result = -1;

 while (low <= high) {
  mid = (low + high)/2;
  if (x[mid] > n) {
   high = mid - 1;
  } else if (x[mid] < n) {
   low = mid + 1;
  } else {
   result = mid;
   high = mid - 1;
  }
 }

 return result;
}