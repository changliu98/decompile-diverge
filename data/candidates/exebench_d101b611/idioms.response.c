int and_peep2_q(int i, int *ip)
{
  *ip = i & ~1;
  return i;
}