
long ff_atomic_dec_long(volatile long *val)
{
 return __sync_sub_and_fetch(val, 1);
}
