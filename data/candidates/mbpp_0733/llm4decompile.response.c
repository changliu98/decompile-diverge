int func0(int A[], int n, int x)
{
 int left = 0, right = n - 1;
 int mid;
 int result = -1;

 while (left <= right) {
  mid = left + (right - left) / 2;
  if (A[mid] == x) {
   result = mid;
   right = mid - 1;
  } else if (A[mid] > x) {
   right = mid - 1;
  } else {
   left = mid + 1;
  }
 }

 return result;
}