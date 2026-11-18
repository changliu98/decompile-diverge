int limit(int i)
{
  if (i < -32768 / 2)
    return -32768 / 2;
  if (i > 32768 / 2 - 1)
    return 32768 / 2 - 1;
  return i;
}