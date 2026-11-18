int *func0(int n, int *size)
{
 int i;
 int *arr = malloc(sizeof(int) * 32);
 *size = 0;

 for (i = 2; i * i <= n; i++) {
  while (n % i == 0) {
   arr[(*size)++] = i;
   n /= i;
  }
 }

 if (n > 1)
  arr[(*size)++] = n;

 return arr;
}