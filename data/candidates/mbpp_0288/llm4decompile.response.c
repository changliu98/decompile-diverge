int func0(int *arr, int N, int P)
{
 int i, count = 0;
 for (i = 0; i < N; i++)
  if (((arr[i] * arr[i]) % P) == 1)
   count++;
 return count;
}