double drand48(unsigned int *state)
{
  int rand = (int)(*state * 16807) - (int)((int)(*state * 16807) / 0x100000000L * 2147483647);
  *state = rand;
  return (double)rand / 2147483647;
}