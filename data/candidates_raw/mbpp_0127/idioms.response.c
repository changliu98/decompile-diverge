int rec_add(int a, int b)
{
  if (b < 0)
    return -rec_add(a, -b);
  if (b == 0)
    return 0;
  if (b == 1)
    return a;
  return rec_add(a, b - 1) + a;
}