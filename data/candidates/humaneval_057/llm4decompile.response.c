int func0(float *l, int size)
{
 int i;
 int incr = 0;
 int decr = 0;

 for (i = 1; i < size; i++)
 {
  if (l[i] > l[i - 1])
  {
   incr = 1;
  }

  if (l[i] < l[i - 1])
  {
   decr = 1;
  }
 }

 if (incr + decr == 2)
 {
  return 0;
 }
 else
 {
  return 1;
 }
}