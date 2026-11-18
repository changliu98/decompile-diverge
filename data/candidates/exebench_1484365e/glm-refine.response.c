int atomic32_increment(int *dest)
{
  return _InterlockedIncrement(dest);
}