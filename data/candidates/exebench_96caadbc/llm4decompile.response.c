long ihk_atomic_add_long_return(long delta, long *target)
{
 long ret;

 LOCK();
 ret = *target + delta;
 *target += delta;
 UNLOCK();

 return ret;
}