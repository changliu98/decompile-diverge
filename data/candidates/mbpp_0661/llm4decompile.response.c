int func0(int arr[], int n)
{
 int sum[200];
 int max1, max2, max3;
 int i;

 if (n >= 1)
  sum[0] = arr[0];
 if (n >= 2)
  sum[1] = arr[0] + arr[1];
 if (n >= 3) {
  sum[2] = ((arr[0] + arr[1]) > (arr[0] + arr[2]) ? (arr[0] + arr[1]) : (arr[0] + arr[2]));
  sum[2] = ((sum[1]) > (sum[2]) ? (sum[1]) : (sum[2]));
 }

 for (i = 3; i < n; i++) {
  max1 = sum[i - 1];
  max2 = arr[i] + sum[i - 2];
  max3 = arr[i] + arr[i - 1] + sum[i - 3];
  max2 = ((max1) > (max2) ? (max1) : (max2));
  max3 = ((max2) > (max3) ? (max2) : (max3));
  sum[i] = max3;
 }

 return sum[n - 1];
}