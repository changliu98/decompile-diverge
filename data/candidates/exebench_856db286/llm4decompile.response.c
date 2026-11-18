int _hclib_atomic_dec_relaxed(volatile int *target)
{
  int result;
  LOCK();
  result = --(*target);
  UNLOCK();
  return result;
}