void decrease_order(int *num1, int *diff)
{
 int tmp;
 if (*num1 < *diff) {
  tmp = *num1;
  *num1 = *diff;
  *diff = tmp;
 }
}