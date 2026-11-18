int func0(int *q, int size, int w)
{
 int i;
 int sum = 0;
 for (i = 0; i < size / 2; i ++) {
  if (q[i] != q[size - 1 - i]) {
   return 0;
  }
  sum += q[i];
  sum += q[size - 1 - i];
 }
 if (size % 2 == 1) {
  sum += q[size / 2];
 }
 if (sum > w) {
  return 0;
 }
 return 1;
}