static long AddUintptr(long *ptr, long inc)
{
 return __sync_fetch_and_add(ptr, inc) + inc;
}