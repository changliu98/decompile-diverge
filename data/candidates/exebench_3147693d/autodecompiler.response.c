unsigned long int
nrt_testing_atomic_inc(unsigned long int *num)
{
 unsigned long int ret;

 ret = *num;
 ret++;
 *num = ret;

 return ret;
}