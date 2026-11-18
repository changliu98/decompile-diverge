unsigned long int
increment(unsigned long int *num)
{
 unsigned long int ret;

 ret = *num;
 ret++;
 *num = ret;

 return ret;
}