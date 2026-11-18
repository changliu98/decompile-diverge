int func0(int *arr, int n, int i)
{
 int left_child = 2 * i + 1;
 int right_child = 2 * i + 2;

 if (left_child > n)
  return 1;

 int left_res = 0;
 if (arr[i] <= arr[left_child])
  left_res = func0(arr, n, left_child);

 int right_res = 1;
 if (right_child != n)
 {
  right_res = 0;
  if (arr[i] <= arr[right_child])
   right_res = func0(arr, n, right_child);
 }

 return left_res && right_res;
}