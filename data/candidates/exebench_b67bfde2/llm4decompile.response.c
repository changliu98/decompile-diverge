int wdl_atomic_incr(wdl_atomic_t *v)
{
  int rv;
  LOCK();
  rv = ++(*v);
  UNLOCK();
  return rv;
}