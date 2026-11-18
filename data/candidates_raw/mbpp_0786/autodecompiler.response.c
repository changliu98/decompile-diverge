int find_first_larger(int *A, int aLen, int key)
{
 int lo = 0;
 while (1)
 {
  if (lo >= aLen || A[lo] > key) return lo;
  lo++;
 }
}