void func0(int arr[], int n, int sum_mul[])
{
 int mul = 1, sum = 0;
 int i = 0;

 while (1) {
  if (i >= n)
   break;
  sum += arr[i];
  mul *= arr[i];
  i++;
 }

 sum_mul[0] = sum;
 sum_mul[1] = mul;
}