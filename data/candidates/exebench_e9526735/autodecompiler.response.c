void
removeslave(int *a, int n)
{
 int i = 10 - 1;

 while (1) {
  if (i < 0)
   return;
  if (a[i] != 0) {
   a[i] = 0;
   n--;
  }
  if (n == 0)
   return;
  i--;
 }
}