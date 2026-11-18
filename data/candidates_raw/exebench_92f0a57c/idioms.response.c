static double next_rand(void *data)
{
  struct _rand *rand = (rand_t *)data;
  rand->seed = (rand->seed * 1103515245 + 12345);
  return (rand->seed & 0x7fff) / (double)0x7fff;
}