void constrain_int(int min, int max, int *val)
{
 if (*val < min) {
  *val = min;
  return;
 }
 if (*val > max) {
  *val = max;
  return;
 }
}