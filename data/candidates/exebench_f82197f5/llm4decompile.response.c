void UNLOCK(int *f)
{
  int i;
  LOCK();
  i = *f;
  *f = *f - 1;
  UNLOCK();
  if (i == 1)
    return;
  if (i == 2)
  {
    LOCK();
    *f = 0;
    UNLOCK();
    syscall(202, f, 1);
  }
}