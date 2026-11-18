static long _increment_and_fetch(long *ptr, long inc)
{
 return __sync_fetch_and_add(ptr, inc) + inc;
}