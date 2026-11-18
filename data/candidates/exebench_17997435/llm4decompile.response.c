int trylock(int *lock)
{
 int ret;
 LOCK();
 ret = !*lock;
 *lock = 1;
 UNLOCK();
 return ret;
}