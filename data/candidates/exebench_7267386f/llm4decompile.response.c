int _hclib_atomic_dec_release(volatile int *target)
{
  int result;
  LOCK();
  result = --(*target);
  UNLOCK();
  return result;
}