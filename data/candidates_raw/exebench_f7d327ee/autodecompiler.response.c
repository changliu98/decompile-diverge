unsigned long long __addvdi3(unsigned long long a, unsigned long long b, int *overflow)
{
 unsigned long long ret;
 char no_overflow = 0;

 if (*overflow)
 {
  unsigned long long max_value = ((unsigned long long) 0xffffffff) + ((unsigned long long) 0xffffffff);
  unsigned long long min_value = ((unsigned long long) 0x80000000) + ((unsigned long long) 0x80000000);

  unsigned long long sum = a + b;

  unsigned long long *max_ptr = (unsigned long long *) &max_value;
  unsigned long long *min_ptr = (unsigned long long *) &min_value;
  unsigned long long *sum_ptr = (unsigned long long *) &sum;

  if (a > b)
  {
   no_overflow = (sum_ptr[0] >= max_ptr[0]) && (sum_ptr[1] >= max_ptr[1]);
  }
  else
  {
   no_overflow = (sum_ptr[0] >= min_ptr[0]) && (sum_ptr[1] >= min_ptr[1]);
  }
 }

 *overflow = no_overflow & 1;

 if (*overflow)
 {
  ret = a + b;
 }
 else
 {
  ret = 0;
 }

 return ret;
}