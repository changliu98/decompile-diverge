int and_peep2_qi(int val, int *mask)
{
  *mask = val & 0x5f;
  return val;
}