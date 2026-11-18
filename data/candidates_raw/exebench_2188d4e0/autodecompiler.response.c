void adjust_size(int *size1, int *size2)
{
 if (*size1 > *size2) {
  int *tmp = size1;
  *tmp /= 2;
  *size2 *= 2;
  return;
 }
 *size1 *= 2;
 int *tmp = size2;
 *tmp /= 2;
}