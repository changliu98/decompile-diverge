unsigned int
and_peep2_q (unsigned int y, unsigned int *x)
{
  *x = y & 0xfe;
  return y;
}