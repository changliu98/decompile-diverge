void func0(int *arr, int len)
{
 if (len < 2)
  return;
 int mid = len / 2;
 int *left = malloc((size_t) mid * sizeof(int));
 int *right = malloc((size_t) (len - mid) * sizeof(int));
 int i;
 for (i = 0; i < mid; i++)
  left[i] = arr[i];
 for (i = mid; i < len; i++)
  right[i - mid] = arr[i];
 func0(left, mid);
 func0(right, len - mid);
 merge(left, mid, right, len - mid, arr);
 free(left);
 free(right);
}