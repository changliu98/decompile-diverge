void set(int *set, int i)
{
  set[i / 32] |= (1 << (i % 32));
}